from tkinter import *
import pandas as pd
import os, sys
import time
from PIL import ImageTk,Image

def parse():
    resultado = Tk()
    resultado.geometry("300x300")
    query = sql.get() 
    stringlist = query.split()
    operacion = stringlist[0]
    if(operacion.lower() == "select"):
        if ()




    elif(operacion.lower()  == "insert"):
        #into = stringlist[1]
        if(stringlist[2].lower() != "dhash"):
            Label(resultado,text ='Ingrese una tabla correcta!', width= 20 , height = 20 ,font = large_font).pack()
            resultado.mainloop()
            return 
        else:
            if(stringlist[3] == "" or stringlist[4] == "" or stringlist[5] == "" or stringlist[6] == ""):
                Label(resultado,text ='Ingrese un registro correcto!!', width= 20 , height = 20 ,font = large_font).pack()
                resultado.mainloop()
                return 
            bashcomand = "g++ insert_register.cpp"
            os.system(bashcomand)
            bashcomand = "./a.out " + stringlist[3] + " " + stringlist[4] + " " + stringlist[5] + " " + stringlist[6] 
            os.system(bashcomand)
            Label(resultado,text ='Insertado correctamete!', width= 20 , height = 20 ,font = large_font).pack()
            resultado.mainloop()
            return 
#devuelve todas los registros de la tabla 
#como hacemos cuando el select es *         
#que el table name sea DHASH siempre
#tenemos que soportar este tipo de busqueda select * from tabla where ID = ASDGB
root = Tk()
root.title("Base de datos 2 Proyecto")
large_font = ('Verdana',30)

image2 =Image.open('menu.jpeg')
image1 = ImageTk.PhotoImage(image2)
img = Label(root, image = image1)
img.pack()

label = Label(root, text="Ingrese su SQL query")
label.config(bg = "black", fg="red", font=("Times new Roman",24))
label.place(x = 320, y = 20) 

sql = StringVar() 
text = Entry(root, textvariable = sql,width = 30, font = large_font)
text.place(x = 100 , y = 100)

button2 = Button(root, text = "Run Query", command=parse , font = large_font)
button2.place(y = 330,x= 350)

root.geometry("960x540")
root.mainloop()