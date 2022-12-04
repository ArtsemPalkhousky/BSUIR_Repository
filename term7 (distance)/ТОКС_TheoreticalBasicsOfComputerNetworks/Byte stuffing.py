import threading
from tkinter import *
import serial
import hashlib

# 0f05e4a0122010c00c88888888
DATA_LENGTH_DEC = 9 * 2
DATA_LENGTH_HEX_STRING = str(hex(int(DATA_LENGTH_DEC/2)))[2:].rjust(2, '0')
PACKET_LENGTH_DEC_STRING = DATA_LENGTH_DEC + 4 * 2
FLAG_HEX_STRING = '0f'
BYTE_STAFFING = '03'


def check_packet(packet: str) -> bool:
    print(DATA_LENGTH_HEX_STRING)
    if len(packet) != PACKET_LENGTH_DEC_STRING:
        app.make_log("Packet length not correct")
        return False
    try:
        hex(int(packet[0:PACKET_LENGTH_DEC_STRING], 16))
    except ValueError:
        app.make_log("The entered package does not consist of hexadecimal")
        return False
    if packet[0:2] != FLAG_HEX_STRING:  # Packet start flag
        app.make_log("Invalid packet start flag")
        return False
    if packet[2:4] != DATA_LENGTH_HEX_STRING:  # Data length
        app.make_log("Bad flag length")
        return False
    if packet[4:6]:  # Source Address
        pass
    if packet[6:8]:  # Destination Address
        pass
    if packet[8:DATA_LENGTH_DEC]:  # Data
        pass
    return True


def make_byte_stuffing(packet: str) -> str:
    print(packet)
    out = packet[0:2] + packet[2:].replace(BYTE_STAFFING, BYTE_STAFFING + BYTE_STAFFING).replace(FLAG_HEX_STRING, BYTE_STAFFING + FLAG_HEX_STRING)
    print(out)
    return out


def byte_destuffing(packet: str) -> str:
    print(packet)
    out = packet[0:2] + packet[2:].replace(BYTE_STAFFING + BYTE_STAFFING, BYTE_STAFFING).replace(BYTE_STAFFING + FLAG_HEX_STRING, FLAG_HEX_STRING)
    print(out)
    return out


def check_sum(packet: str) -> str:
    checksum = str(hashlib.md5(packet.encode('cp1251')).hexdigest())
    return checksum


def make_thread_for_reader():
    tr_in = threading.Thread(target=app.read_data)
    tr_in.daemon = True
    tr_in.start()


class MainWindow:
    def __init__(self):
        self.root = Tk()
        self.root.title('Laba2')
        self.root.geometry('1440x820')
        self.input_textbox = Text(self.root, font="Arial 10")
        self.output_textbox = Text(self.root, font="Arial 10")
        self.log_textbox = Text(self.root, font="Arial 10")
        self.bit_staffing_textbox = Text(self.root, font="Arial 10")
        self.input_textbox.place(width=360, height=620, x=0, y=100)
        self.bit_staffing_textbox.place(width=360, height=620, x=360, y=100)
        self.output_textbox.place(width=360, height=620, x=720, y=100)
        self.log_textbox.place(width=360, height=620, x=1080, y=100)
        self.input_label = Label(self.root, text="Sent", anchor="center", font="Arial 30")
        self.bit_staffing_label = Label(self.root, text="Byte Staffing", anchor="center", font="Arial 30")
        self.output_label = Label(self.root, text="Recieved", anchor="center", font="Arial 30")
        self.log_label = Label(self.root, text="Logs", anchor="center", font="Arial 30")
        self.input_label.place(width=360, height=100, x=0, y=0)
        self.bit_staffing_label.place(width=360, height=100, x=360, y=0)
        self.output_label.place(width=360, height=100, x=720, y=0)
        self.log_label.place(width=360, height=100, x=1080, y=0)
        self.output_textbox.config(state='disabled')
        self.log_textbox.config(state='disabled')
        self.bit_staffing_textbox.config(state='disabled')
        self.send_button = Button(text="Send", command=self.send_button_click, font="Arial 30")
        self.send_button.place(width=720, height=100, x=0, y=720)
        self.clear_button = Button(text="Clear", command=self.clear_button_click, font="Arial 30")
        self.clear_button.place(width=720, height=100, x=720, y=720)
        self.input_textbox.bind("<KeyRelease>", self.on_button_clicked)
        self.data_last_poss = 0
        self.counter = 0
        self.port1 = serial.Serial()
        self.port2 = serial.Serial()
        try:
            self.port1 = serial.Serial('COM3', 115200)
            self.port2 = serial.Serial('COM4', 115200)
            self.make_log('Ports are open')
        except serial.SerialException:
            self.make_log("Can't open ports")

    def on_button_clicked(self, event):
        print(event.keycode)
        if event.keycode == 22:
            if self.counter != 0:
                self.counter -= 1
        elif event.keycode == 114 or event.keycode == 113 or event.keycode == 111 or event.keycode == 116:
            pass
        elif self.counter != PACKET_LENGTH_DEC_STRING:
            self.counter += 1
        elif self.counter == PACKET_LENGTH_DEC_STRING:
            self.make_log("Maximum package length reached")
            self.input_textbox.delete('end-2c', END)
        print(self.counter)

    def send_button_click(self):
        self.input_textbox.config(state='normal')
        data = self.input_textbox.get(1.0, END)
        packet = data[self.data_last_poss:len(data) - 1]
        if check_packet(packet):
            print(packet)
            checksum = check_sum(packet)
            self.make_log("Sender checksum = " + checksum)
            packet += checksum
            byte_stuffed_packet = make_byte_stuffing(packet)
            self.bit_staffing_textbox.config(state='normal')
            self.bit_staffing_textbox.insert(END, byte_stuffed_packet + '\n')
            self.bit_staffing_textbox.config(state='disabled')
            self.send_data(byte_stuffed_packet)
        self.data_last_poss = len(data)
        self.input_textbox.insert(END, '\n')
        self.counter = 0

    def send_data(self, data):
        try:
            self.port1.write(data.encode('cp1251'))
        except serial.PortNotOpenError:
            self.make_log('Ports are closed')

    def read_data(self):
        out = ''
        while 1:
            while self.port2.inWaiting() > 0:
                self.output_textbox.config(state='normal')
                try:
                    out += self.port2.read().decode('cp1251')
                except serial.PortNotOpenError:
                    self.make_log('Ports are closed')
            if out != '':
                print(out)
                out = byte_destuffing(out)

                out_check_sum = check_sum(out[0:PACKET_LENGTH_DEC_STRING])
                if out_check_sum != out[PACKET_LENGTH_DEC_STRING:]:
                    self.make_log("Sender and receiver checksums are not equal")
                else:
                    self.make_log("Reciever checksum = " + out_check_sum)
                    self.output_textbox.insert(END, out[0:PACKET_LENGTH_DEC_STRING] + '\n')
                out = ''
                self.output_textbox.config(state='disabled')

    def make_log(self, message):
        self.log_textbox.config(state='normal')
        self.log_textbox.insert(END, message + '\n')
        self.log_textbox.config(state='disabled')

    def clear_button_click(self):
        self.input_textbox.config(state='normal')
        self.output_textbox.config(state='normal')
        self.bit_staffing_textbox.config(state='normal')
        self.input_textbox.delete(1.0, END)
        self.output_textbox.delete(1.0, END)
        self.bit_staffing_textbox.delete(1.0, END)
        self.output_textbox.config(state='disabled')
        self.bit_staffing_textbox.config(state='disabled')
        self.data_last_poss = 0
        self.counter = 0
        self.make_log("Screen is cleared")


if __name__ == "__main__":
    app = MainWindow()
    make_thread_for_reader()
    app.root.mainloop()
