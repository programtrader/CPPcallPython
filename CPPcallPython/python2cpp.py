#测试C++调用python
def add(a,b):
    print("in python function add")
    print("a=" + str(a))
    print("b=" + str(b))
    pirnt("return=" + str(a+b))
    return

def foo(a):
    print("in python function foo")
    print("a="+str(a))
    print("return="+str(a*a))
    return


