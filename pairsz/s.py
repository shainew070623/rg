import random  #引入随机数模块
from tkinter import *   #为图形化界面做准备
import tkinter as tk
from tkinter.ttk import *
n=10       #默认题目最大值
number=1   #默认题目个数
flag=0     #判断是否有小数的标记位
flag1=0    #判断输出方式的标记位
s=""
root = Tk()
root.title('四则运算')
root.geometry('600x500')

#点击确定按钮触发的操作
def Mysel():
    f = open("四则运算.txt", "w")  #打开文件并清空文件
    f.write("")
    text.delete('1.0','end')    #清空文本框
    global number
    number = int(inp1.get())     #获取输入框内容
    global n
    n = int(inp2.get())
    global flag
    flag=var1.get()
    global flag1
    flag1=var2.get()
    ss = var.get()
    if ss==0:
        for i in range(number):
            add(i)
    elif ss==1:
        for i in range(number):
            sub(i)
    elif ss==2:
        for i in range(number):
            mul(i)
    elif ss==3:
        for i in range(number):
            div(i)
    elif ss==4:
        for i in range(number):
            mix(i)
    f.close()

#图形化界面设置
lb = Label(root)
lb.pack()
text = Text(root,x=0,y=0, width=40, height=100)
text.pack(anchor=W)

Lab1=Label(root,text='题目个数').place(x=300,y=20)
default_value = StringVar()
default_value.set('1')
inp1 = Entry(root,textvariable = default_value)
inp1.place(x=400, y=20, width=100, height=20)

Lab2=Label(root,text='题目最大值').place(x=300,y=80)
default_value1 = StringVar()
default_value1.set('10')
inp2 = Entry(root,textvariable=default_value1)
inp2.place(x=400, y=80, width=100, height=20)

Lab3=Label(root,text='运算类型').place(x=300,y=150)
var=tk.IntVar()

checkadd=tk.Radiobutton(root,text="+",variable=var, value=0,
                 ).place(x=400,y=150)

checksub=tk.Radiobutton(root,text="-",variable=var, value=1,
                 ).place(x=450,y=150)

checkmul=tk.Radiobutton(root,text="*",variable=var, value=2,
                 ).place(x=500,y=150)

checkdiv=tk.Radiobutton(root,text="/",variable=var, value=3,
                ).place(x=550,y=150)

checkmix=tk.Radiobutton(root,text="mix",variable=var, value=4,
                ).place(x=400,y=180)

Lab3=Label(root,text='小数').place(x=300,y=210)
var1 = tk.IntVar()
checkis=tk.Radiobutton(root,text="Y",variable=var1, value=1,
                ).place(x=400,y=210)
checkno=tk.Radiobutton(root,text="N",variable=var1, value=0,
                ).place(x=450,y=210)

Lab4=Label(root,text='输出方式').place(x=300,y=270)
var2 = tk.IntVar()
checkis=tk.Radiobutton(root,text="直接打印",variable=var2, value=0,
                ).place(x=400,y=270)
checkno=tk.Radiobutton(root,text="写入文件",variable=var2, value=1,
                ).place(x=500,y=270)

btn1 = Button(root, text='确定', command=Mysel)
btn1.place(x=400, y=400, width=50, height=20)
#加法运算
def add(i):
    if flag==0:
        a=random.randint(0,n)
        b=random.randint(0,n)
    else:
        a=random.uniform(0,n)
        a=round(a,2)
        b=random.uniform(0,n)
        b=round(b,2)
    global s
    s=str(i+1)+": "+str(a)+" + "+str(b)+"="
    s1=round(a+b,2)
    if flag1==0:
       s=s+'\n'
       text.insert(INSERT, s)
    else:
        f=open("四则运算.txt","a+")
        f.write(s)
        f.write("\n")
        f.close()
    return a+b
#减法运算
def sub(i):
    if flag==0:
        a=random.randint(0,n)
        b=random.randint(0,n)
    else:
        a=random.uniform(0,n)
        a=round(a,2)
        b=random.uniform(0,n)
        b=round(b,2)
    global s
    s=str(i+1)+": "+str(a)+" - "+str(b)+"="
    s1 = round(a - b, 2)
    if flag1==0:
        s = s + '\n'
        text.insert(INSERT, s)
    else:
        f=open("四则运算.txt","a+")
        #   f.write(s+str(s1))
        f.write(s)
        f.write("\n")
        f.close()
    return a-b
#除法运算
def div(i):
    if flag==0:
        a=random.randint(0,n)
        b=random.randint(1,n)
    else:
        a=random.uniform(0,n)
        a=round(a,2)
        b=random.uniform(1,n)
        b=round(b,2)
    s=str(i+1)+": "+str(a)+" ÷ "+str(b)+"="
    s1=round(a/b,2)
    if flag1==0:
        s = s + '\n'
        text.insert(INSERT, s)
    else:
        f=open("四则运算.txt","a+")
        #   f.write(s+str(s1))
        f.write(s)
        f.write("\n")
        f.close()
    return s1
#乘法运算
def mul(i):
    if flag==0:
        a=random.randint(0,n)
        b=random.randint(0,n)
    else:
        a=random.uniform(0,n)
        a=round(a,2)
        b=random.uniform(0,n)
        b=round(b,2)
    s=str(i+1)+": "+str(a)+" * "+str(b)+"="
    s1 = round(a * b, 2)
    if flag1==0:
        s = s + '\n'
        text.insert(INSERT, s)
    else:
        f=open("四则运算.txt","a+")
        #   f.write(s+str(s1))
        f.write(s)
        f.write("\n")
        f.close()
    return a*b
#混合运算
def mix(i):
    op=['+','-','*','÷']
    if flag==0:
        a=random.randint(0,n)
        b=random.randint(0,n)
        c=random.randint(0,n)
    else:
        a=random.uniform(0,n)
        a=round(a,2)
        b=random.uniform(0,n)
        b=round(b,2)
        c = random.uniform(0, n)
        c = round(c, 2)
    ch1=random.randint(0,1)
    ch2=random.randint(1,2)
    if ch1==ch2:
        s=str(i+1)+": "+str(a)+str(op[random.randint(0,3)])+"("+str(b)+str(op[random.randint(0,3)])+str(c)+")"+"="+"\n"
    if ch1==0 and ch2==1:
        s=str(i+1)+": "+"("+str(a)+str(op[random.randint(0, 3)])+str(b)+")"+str(op[random.randint(0, 3)])+str(c)+"="+"\n"
    if ch1==0 and ch2==2:
        s=str(i+1)+": "+"("+str(a)+str(op[random.randint(0, 3)])+str(b)+str(op[random.randint(0, 3)])+str(c)+")"+"="+"\n"
    if ch1==1 and ch2==2:
        s=str(i+1)+": "+str(a)+str(op[random.randint(0, 3)])+"("+str(b)+str(op[random.randint(0, 3)])+str(c)+")"+"="+"\n"
    if flag1==0:
        text.insert(INSERT, s)
    if flag1==1:
        f=open("四则运算.txt","a+")
        f.write(s)
        f.close()
    return
root.mainloop()



