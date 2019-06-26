import ctypes


dll = ctypes.WinDLL("dll/CreateDLL.dll")
print(dll.test02(1, 102))
