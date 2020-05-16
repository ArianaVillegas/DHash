from tkinter import *
import pandas as pd
import os, sys
import time
from PIL import ImageTk,Image

#0 todo
#1 codigo
#2 nombre
#3 apellido
#4 carrera

def parse():
    resultado = Tk()
    resultado.geometry("300x300")
    resultado.title('Resultados')
    query = sql.get() 
    stringlist = query.split()
    if (len(stringlist) != 4 and len(stringlist) != 8 and len(stringlist) != 7 ):
        Label(resultado, text = "Ingresaste mal el query").pack()
        resultado.mainloop()
        return
    operacion = stringlist[0]
    if(operacion.lower() == "select"):
        if (stringlist[1] == "*"):
            cod = 0
        elif (stringlist[1].lower() == "codigo"):
            cod = 1
        elif (stringlist[1].lower() == "nombre"):
            cod = 2
        elif (stringlist[1].lower() == "apellidos"):
            cod = 3
        elif (stringlist[1].lower() == "carrera"):
            cod = 4
        else: 
            #fail
            Label(resultado, text = "Ingresaste mal el atributo").pack()
            resultado.mainloop()
            return
        if(stringlist[2].lower() != "from" or stringlist[3].lower() != "dhash"):
            Label(resultado, text = "Ingresaste mal el atributo").pack()
            resultado.mainloop()
            return
        if(len(stringlist) == 4): 
            bashcomand = "g++ printall.cpp"
            os.system(bashcomand)
            final = './a.out ' + str(cod) + ' > all.txt'
            time.sleep(2)
            os.system(final)
            file = open("all.txt")
            scrollbar = Scrollbar(resultado)
            scrollbar.pack( side = RIGHT, fill = Y )
            mylist = Listbox(resultado, yscrollcommand = scrollbar.set )
            lines = file.readlines()
            for line in lines:
                label = Label(resultado, text=line.strip())
                label.pack()
            

        elif(len(stringlist) == 7 and stringlist[4].lower() == "where"): 
            if(stringlist[5].lower() == "codigo"):
                os.system("g++ show_register.cpp")
                bashcomand = './a.out ' + stringlist[6]+ ' ' + str(cod) + ' > show_register.txt'
                os.system(bashcomand)
                file = open("show_register.txt")
                lines = file.readlines()
                for line in lines:
                    label = Label(resultado, text=line.strip())
                    label.pack()
            else:
                Label(resultado, text = "Ingresaste mal el atributo", font= large_font).pack()
                resultado.mainloop()
                return
        else: 
            Label(resultado, text = "Ingresaste mal el atributo", font= large_font).pack()
            resultado.mainloop()
            return
    #insert into dhash values asdf asdfs asdf fasd
    elif(operacion.lower()  == "insert"):
        #into = stringlist[1]
        if(stringlist[2].lower() != "dhash" or stringlist[1].lower() != "into"or stringlist[3].lower() != "values" or len(stringlist) != 8):
            Label(resultado,text ='Ingrese una query correcta!', width= 20 , height = 20 ,font = large_font).pack()
            resultado.mainloop()
            return 
        else:
            bashcomand = "g++ insert_register.cpp"
            os.system(bashcomand)
            bashcomand = "./a.out " + stringlist[4] + " " + stringlist[5] + " " + stringlist[6] + " " + stringlist[7] 
            os.system(bashcomand)
            Label(resultado,text ='Insertado correctamete!', width= 20 , height = 20 ,font = large_font).pack()
            resultado.mainloop()
            return 

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