import tkinter as tk
import serial
import threading

# Thiết lập cổng COM
COM_PORT = "COM8"
BAUD_RATE = 9600

# Tạo cửa sổ GUI
window = tk.Tk()
window.title("Dữ liệu từ ATmega16A")

# Trang trí khung cho phần mềm
frame = tk.Frame(window, bd=2, relief="sunken")
frame.pack(padx=10, pady=50)

# Thêm tên các thành viên trong nhóm
team_label = tk.Label(frame, text="Team-1 Members:\n- Member 1: Nguyen Cong Binh\n- Member 2: Nguyen Lam Thai\n- Member 3: Nguyen Viet Anh", font=("Arial", 14))
team_label.pack(pady=10)

# Nhãn hiển thị dữ liệu
label = tk.Label(window, text="Object Count: 0", font=("Arial", 24))
label.pack(pady=20)

# Mở cổng COM8 với tốc độ baud là 9600
try:
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
except serial.SerialException as e:
    label.config(text=f"Error: {e}")
    ser = None

# Hàm nhận dữ liệu từ UART
def read_serial_data():
    if ser:
        while True:
            if ser.in_waiting > 0:
                # Đọc dữ liệu từ cổng COM
                data = ser.read(1)
                if data:
                    object_counter = ord(data)  # Chuyển byte thành giá trị integer
                    label.config(text=f"Object Count: {object_counter}")

# Hàm gửi lệnh xuống vi điều khiển và thay đổi trạng thái nút
def send_command(command, button, state_var):
    if ser:
        ser.write(bytes([command]))
        # Toggle trạng thái
        state_var.set(not state_var.get())
        # Đổi màu nền theo trạng thái
        if state_var.get():
            button.config(bg="red")
        else:
            button.config(bg=button.master.cget("bg"))

# Tạo luồng để đọc dữ liệu từ UART mà không bị gián đoạn giao diện
if ser:
    thread = threading.Thread(target=read_serial_data)
    thread.daemon = True
    thread.start()

# Biến trạng thái cho từng nút
state1 = tk.BooleanVar(value=False)
state2 = tk.BooleanVar(value=False)
state3 = tk.BooleanVar(value=False)

# Tạo các nút bấm để gửi lệnh
button1 = tk.Button(window, text="Toggle Count In", command=lambda: send_command(1, button1, state1))
button1.pack(pady=10)

button2 = tk.Button(window, text="Toggle Count Out", command=lambda: send_command(2, button2, state2))
button2.pack(pady=10)

button3 = tk.Button(window, text="Toggle Buzzer", command=lambda: send_command(3, button3, state3))
button3.pack(pady=10)

# Chạy ứng dụng GUI
window.mainloop()