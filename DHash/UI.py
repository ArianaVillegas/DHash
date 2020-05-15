from tkinter import *
import pandas as pd
import os, sys
import time
from PIL import ImageTk,Image

def cargarmil():
    #os.popen('sh mil.sh')
    bashcomand = "rm *.dat"
    os.system(bashcomand)
    bashcomand = "g++ cargarmil.cpp"
    os.system(bashcomand)
    bashcomand= "./a.out"
    os.system(bashcomand)
def cargardiezmil():
    bashcomand = "rm *.dat"
    os.system(bashcomand)
    bashcomand = "g++ cargardiezmil.cpp"
    os.system(bashcomand)
    bashcomand= "./a.out"
    os.system(bashcomand)
    
def cargarcienmil():
    bashcomand = "rm *.dat"
    os.system(bashcomand)
    bashcomand = "g++ cargarcienmil.cpp"
    os.system(bashcomand)
    bashcomand= "./a.out"
    os.system(bashcomand)

def buscar_registro():
    os.popen('g++ show_register.cpp')
    time.sleep(1)    
    a = registro.get() 
    final = './a.out ' + a + ' > show_register.txt'
    os.popen(final)
    busqueda = Tk()
    busqueda.title("Resultados")
    file = open("show_register.txt")
    lines = file.readlines()
    for line in lines:
        label = Label(busqueda, text=line.strip())
        label.pack()
    txtBusqueda.delete(0,'end')
    busqueda.geometry("400x400")
    busqueda.mainloop()
    

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
    bashcomand = "g++ insert_register.cpp"
    os.system(bashcomand)
    bashcomand = "./a.out " + key.get() + " " + nombre.get() + " " + Apellido.get() + " " + Carrera.get() 
    os.system(bashcomand)
    entrada1.delete(0,'end')
    entrada2.delete(0,'end')
    entrada3.delete(0,'end')
    entrada4.delete(0,'end')
    


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
txtBusqueda = Entry(root,textvariable = registro, width = 20)
txtBusqueda.place(x=380,y=190)


Label(root,text = 'Cargar 1 000 datos: ').place(x=70, y = 80)
button = Button(root, text = "Cargar1", command=cargarmil).place(x=210,y=80)

Label(root,text = 'Cargar 10 000 datos: ').place(x=300, y = 80)
button = Button(root, text = "Cargar2", command=cargardiezmil).place(x=440,y=80)

Label(root,text = 'Cargar 100 000 datos: ').place(x=530,y= 80)
button = Button(root, text = "Cargar3", command=cargarcienmil).place(x=680,y=80)

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
    
entrada1= Entry(root,textvariable = key,width = 20)
entrada1.place(x = 380 ,y =310)
entrada2=Entry(root,textvariable = nombre,width = 20)
entrada2.place(x = 380 ,y =340)
entrada3=Entry(root,textvariable = Apellido,width = 20)
entrada3.place(x = 380 ,y =370)
entrada4=Entry(root,textvariable = Carrera,width = 20)
entrada4.place(x = 380 ,y =400)


button2 = Button(root, text = "Insertar", command=insertRegistro).place(y = 450,x= 420)



root.geometry("960x540")
root.mainloop()