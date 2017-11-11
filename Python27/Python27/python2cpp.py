#test C++ call python
def foo(a):
    print "in python function foo" 
    print "a=" + str(a)
    print "return=" + str(a*a)
    return a*a

def add(a,b):
    print "in python function add"
    print "a=" + str(a)
    print "b=" + str(b)
    print "return=" + str(a+b)
    return a+b

def returnList():
    print "in python function return List"
    a=["ATR",10000,33.3]
    return a
    
def returnDict():
    print "in python function return Dict" 
    a={"Open": 33.33 , "High": 55.55, "Low": 22.22, "Close": 44.44};
    return a

