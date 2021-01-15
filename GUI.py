import serial
import tkinter as tk;
import os

from tkinter import *


class Window(Frame):

    def __init__(self, master=None):
        self.ArduinoSerial = None
        Frame.__init__(self, master)
        self.master = master
        self.pack(fill=BOTH, expand=1)
        self.lable_Temp = Label(text="Temperature Goal:")
        self.lable_Humidity = Label(text="Humidity Goal:")
        self.lable_pwm = Label(text="PWM Goal:")

        self.lable_cTemp = Label();
        self.lable_cHum = Label();
        self.lable_cPWM = Label();

        self.txt_Temp = Entry( root,width=10);
        self.txt_Humidity = Entry( root,width=10);
        self.txt_PWM = Entry(root, width=10);
        self.btnConnect = Button(root, height=1, width=10, text="Connect",command=self.connect())
        self.btnRead = Button(root, height=1, width=10, text="Read")
        self.btnSend = Button(root, height=1, width=10, text="Send",command = self.sendToSerial)

        # Lables plasing
        self.lable_Temp.place(x=0, y=10)
        self.lable_Humidity.place(x=0, y=30)
        self.lable_pwm.place(x=0, y=50)
        # Output Lables
        self.lable_cTemp.place(x=140, y=10)
        self.lable_cHum.place(x=140, y=30)
        self.lable_cPWM.place(x=140, y=50)

        # Txt Boxes
        self.txt_Temp.place(x=125, y=10)
        self.txt_Humidity.place(x=125, y=30)
        self.txt_PWM.place(x=125, y=50)

        self.lable_cTemp.place(x=175, y=10)
        self.lable_cHum.place(x=175, y=30)
        self.lable_cPWM.place(x=175, y=50)

        self.btnConnect.pack()
        self.btnRead.pack()
        self.btnSend.pack();

    def sendToSerial(self):
        # Function to print entry text.
        message = self.txt_Humidity.get()+"/"+self.txt_Temp.get()+"/"+self.txt_PWM.get()+'\n'
        print("Text : ", message)
        self.ArduinoSerial.write(message.encode())
    def connect(self):
        ports = os.popen('python -m serial.tools.list_ports').readlines()
        print(ports)
        if(ports != []):
            print(ports[0])
            self.ArduinoSerial = serial.Serial(ports[0].strip(),9600)
    def getReadings(self):
        self.ArduinoSerial.write("//\n".encode())






root = Tk()
app = Window(root)
root.wm_title("Tkinter button")
root.geometry("320x200")
root.mainloop()