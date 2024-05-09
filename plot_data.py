import matplotlib.pyplot as plt

# Load data from input_signal.dat
with open("input_signal1.dat", "r") as f:
    input_signal = [float(line.strip()) for line in f]

# Load data from output_signal.dat
with open("output_signal1.dat", "r") as f:
    output_signal = [float(line.strip()) for line in f]


#plot the first 100 samples of the input signal and output signal
plt.figure()
plt.plot(input_signal[:300], label="Input Signal")
plt.plot(output_signal[:300], label="Output Signal")
plt.xlabel("Sample")
plt.ylabel("Amplitude")
plt.title("Input and Output Signal")
plt.legend()



# Show plot
plt.show()
