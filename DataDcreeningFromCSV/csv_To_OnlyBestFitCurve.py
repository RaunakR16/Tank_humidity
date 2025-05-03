import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('H:\Paper sensor with TANK\CODE FOR DATA SCREENING\DATA\sensor_data.csv', encoding='latin1')
print(data.head())

# The rest of your code remains the same
y1 = data['Humidity (%)'].values
y2 = data['Paper Sensor Value'].values

# Create a figure and axis
fig, ax1 = plt.subplots(figsize=(12, 6))

# Fit a polynomial curve for y1 (degree 2 for example)
p1 = np.polyfit(np.arange(len(y1)), y1, 2)
y1_fit = np.polyval(p1, np.arange(len(y1)))

# Plot the best fit curve for y1
ax1.plot(np.arange(len(y1)), y1_fit, '-', label="Fit: DHT 11", color='blue', linewidth=2)

ax1.set_xlabel('Time (sec.)', fontsize=20, fontweight='bold')
ax1.set_ylabel('Humidity (DHT11)', fontsize=20, fontweight='bold', color='blue')
ax1.tick_params(axis='y', labelcolor='blue')
ax1.grid(True)

# Create a secondary y-axis for y2
ax2 = ax1.twinx()

# Fit a polynomial curve for y2 (degree 2 for example)
p2 = np.polyfit(np.arange(len(y2)), y2, 2)
y2_fit = np.polyval(p2, np.arange(len(y2)))

# Plot the best fit curve for y2
ax2.plot(np.arange(len(y2)), y2_fit, '-', label="Fit: Paper-based sensor", color='#FF7F50', linewidth=2)

ax2.set_ylabel('Serial value (Paper-based sensor)', fontsize=20, fontweight='bold', color='#FF7F50')
ax2.tick_params(axis='y', labelcolor='#FF7F50')

# Add a title
plt.title('Best Fit Curves from the Sensors', fontsize=20, fontweight='bold')

# Display the plot
plt.show()
