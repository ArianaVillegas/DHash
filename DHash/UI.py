from tkinter import *
import pandas as pd
import os, sys
from PIL import ImageTk,Image

def CargarArchivos():
    os.popen('sh /Documentos/BD2/ProyectoBD2/cargar.sh')
def buscar_registro():
    print(registro.get())
def showResult():
    extern = Tk()
    extern.title("Resultados")
    file = open("resultados.txt")
    lines = file.readlines()
    for line in lines:
        label = Label(extern, text=line.strip())
        label.pack()
    extern.geometry("400x400")
    extern.mainloop()

def insertRegistro(): 
    print(key.get())
    print(nombre.get())
    print(Apellido.get())
    print(Carrera.get())
    
    

root = Tk()
root.title("Base de datos 2 Proyecto")

image2 =Image.open('menu.jpeg')
image1 = ImageTk.PhotoImage(image2)
img = Label(root, image = image1)
img.pack()


key = StringVar()
nombre = StringVar()
Apellido = StringVar()
Carrera = StringVar()

label = Label(root, text="¡Bienvenidos al proyecto BD2!")

label.config(fg="red", font=("Verdana",24))
label.place(x = 215, y = 20) 
registro = StringVar()
txtBusqueda = Entry(root,textvariable = registro, width = 20).place(x=380,y=190)


Label(root,text = 'Cargar 1 000 datos: ').place(x=70, y = 80)
button = Button(root, text = "Cargar", command=CargarArchivos).place(x=210,y=80)

Label(root,text = 'Cargar 10 000 datos: ').place(x=300, y = 80)
button = Button(root, text = "Cargar", command=CargarArchivos).place(x=440,y=80)

Label(root,text = 'Cargar 100 000 datos: ').place(x=530,y= 80)
button = Button(root, text = "Cargar", command=CargarArchivos).place(x=680,y=80)

l= Label(root,text = 'Busca registro')
l.config(fg="blue", font=("Verdana"))
l.place(x=395,y=160)
Label(root, text='Ingresa key: ').place( x= 280, y =190)
button2 = Button(root, text = "Buscar", command=buscar_registro).place(x = 550,y = 190)


label2 = Label(root, text="¡Ingresa un Registro!")
label2.config(fg="blue", font=("Verdana"))
label2.place(x=380, y =280)


Label(root, text = 'Key: ').place(x=300, y = 310)
Label(root, text = 'Nombre: ').place(x=300, y = 340)
Label(root, text = 'Apellido: ').place(x=300, y = 370)
Label(root, text = 'Carrera: ').place(x=300, y = 400)
    
text= Entry(root,textvariable = key,width = 20).place(x = 380 ,y =310)
text2=Entry(root,textvariable = nombre,width = 20).place(x = 380 ,y =340)
text3=Entry(root,textvariable = Apellido,width = 20).place(x = 380 ,y =370)
text4=Entry(root,textvariable = Carrera,width = 20).place(x = 380 ,y =400)

button2 = Button(root, text = "Insertar", command=insertRegistro).place(y = 450,x= 420)

root.geometry("960x540")
root.mainloop()