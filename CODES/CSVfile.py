import serial
import csv
import time

# Number of samples to log
num_samples = 1000

# Change COM port and baud rate
ser = serial.Serial('COM13', 115200, timeout=1)

# Give a CSV file Name
with open('Data01s.csv', mode='a', newline='') as file:
    writer = csv.writer(file)

    # Write header if the file is empty
    if file.tell() == 0:
        writer.writerow(['Timestamp', 'ADC Value'])

    print(f"Started logging {num_samples} analog data samples...")

    try:
        samples_logged = 0
        while samples_logged < num_samples:
            line = ser.readline().decode('utf-8').strip()

            if line.isdigit():
                analog_value = int(line)
                timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                
                writer.writerow([timestamp, analog_value])
                file.flush()
                
                print(f"{timestamp} - Analog Value: {analog_value}")
                
                samples_logged += 1
            else:
                print("Invalid data received, skipping...")

            time.sleep(0.05)  # match 50ms Arduino delay

        print(f"Logging complete: {num_samples} samples saved.")
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        ser.close()
