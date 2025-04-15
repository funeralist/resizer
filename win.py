import ctypes
from ctypes import wintypes

#WINDOW SIZE
T_WIDTH = 1280
T_HEIGHT = 720

#CENTERING
T_X = (ctypes.windll.user32.GetSystemMetrics(0) - T_WIDTH) // 2
T_Y = (ctypes.windll.user32.GetSystemMetrics(1) - T_HEIGHT) // 2


#WIN API CONFIGURATION
user32 = ctypes.WinDLL("user32", use_last_error=True)


#SetWindowPos TYPES CONFIGURATION
user32.SetWindowPos.argtypes = [wintypes.HWND, wintypes.HWND, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, wintypes.UINT]
user32.SetWindowPos.restype = wintypes.BOOL


#GetForegroundWindow TYPE CONFIGURATION
user32.GetForegroundWindow.restype = wintypes.HWND


#GET HANDLE OF CURRENTLY ACTIVE WINDOW
def get_window():
    return user32.GetForegroundWindow()


#SET POSITION AND SIZE OF WINDOW BASED ON HANDLE
def set_window(hwnd, x, y, width, height):
    return user32.SetWindowPos(hwnd, None, x, y, width, height, 0x0004 | 0x0010)


#REGISTER/UNREGISTER HOTKEY
def register_hotkey():
    if user32.RegisterHotKey(None, 1, 0x0002 | 0x0004, 0x4C):
        return True
    else:
        return False


def unregister_hotkey():
    user32.UnregisterHotKey(None, 1)


def main():
    if not register_hotkey():
            return

    try:
        msg = wintypes.MSG()

        while user32.GetMessageW(ctypes.byref(msg), None, 0, 0) != 0:
            if msg.message == 0x0312 and msg.wParam == 1:
                set_window(get_window(), T_X, T_Y, T_WIDTH, T_HEIGHT)
            
            user32.TranslateMessage(ctypes.byref(msg))
            user32.DispatchMessageW(ctypes.byref(msg))

    finally:
        unregister_hotkey()


if __name__ == "__main__":
    main()