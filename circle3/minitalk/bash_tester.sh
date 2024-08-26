
#!/bin/bash

# Replace with the actual PID of the receiver process
PID=16750

# Function to send a signal
send_bit() {
    if [ "$1" -eq 1 ]; then
        kill -s SIGUSR2 $PID
    else
        kill -s SIGUSR1 $PID
    fi
    # Small delay to ensure the signal is processed
    sleep 0.3
}

# Sending "H" (ASCII 72 -> 01001000)
send_bit 0
send_bit 1
send_bit 0
send_bit 0
send_bit 1
send_bit 0
send_bit 0
send_bit 0

# Sending "e" (ASCII 101 -> 01100101)
send_bit 0
send_bit 1
send_bit 1
send_bit 0
send_bit 0
send_bit 1
send_bit 0
send_bit 1

# Sending "l" (ASCII 108 -> 01101100)
send_bit 0
send_bit 1
send_bit 1
send_bit 0
send_bit 1
send_bit 1
send_bit 0
send_bit 0

# Sending "l" (ASCII 108 -> 01101100)
send_bit 0
send_bit 1
send_bit 1
send_bit 0
send_bit 1
send_bit 1
send_bit 0
send_bit 0

# Sending "o" (ASCII 111 -> 01101111)
send_bit 0
send_bit 1
send_bit 1
send_bit 0
send_bit 1
send_bit 1
send_bit 1
send_bit 1

# Sending " " (ASCII 32 -> 00100000)
#send_bit 0
#send_bit 0
#send_bit 1
#send_bit 0
#send_bit 0
#send_bit 0
#send_bit 0
#send_bit 0

# Sending "W" (ASCII 87 -> 01010111)
#send_bit 0
#send_bit 1
#send_bit 0
#send_bit 1
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 1

# Sending "o" (ASCII 111 -> 01101111)
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 1
#send_bit 1

# Sending "r" (ASCII 114 -> 01110010)
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 1
#send_bit 0
#send_bit 0
#send_bit 1
#send_bit 0

# Sending "l" (ASCII 108 -> 01101100)
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 0
#send_bit 0

# Sending "d" (ASCII 100 -> 01100100)
#send_bit 0
#send_bit 1
#send_bit 1
#send_bit 0
#send_bit 0
#send_bit 1
#send_bit 0
#send_bit 0
