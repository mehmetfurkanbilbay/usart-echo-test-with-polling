# STM32F401RE UART Echo Test (Polling Mode)

This repository contains an implementation of a UART Echo application using the **USART2** peripheral on the **STM32F401RE (Nucleo-F401RE)** development board.

The application continuously polls the receive line. When a byte is successfully received without hardware errors, it echoes (transmits) the exact same byte back to the sender.

---

## 🛠️ Hardware & Clock Specifications

*   **Microcontroller:** STM32F401RE (Cortex-M4)
*   **Clock Configuration:** Default **16 MHz HSI** (Internal High-Speed) oscillator.
*   **Peripheral Bus:** **APB1 Low-Speed Bus** running at **16 MHz**.
*   **Baud Rate:** **9600**
*   **BRR Calculation:**
    $$
    \text{USARTDIV} = \frac{16,000,000}{16 \times 9600} = 104.1667
    $$
    *   **Mantissa (Tam Kısım):** 104 → `0x68`
    *   **Fraction (Kesir Kısmı):** 0.1667 × 16 ≈ 2.66 → Yuvarlama ile `3` (`0x3`)
    *   **USART2->BRR Value:** `0x0683`

---

## 📌 Pin Mapping (Alternate Function 7)

| Peripheral | Pin | Function | Register Setup |
| :--- | :--- | :--- | :--- |
| **USART2_TX** | PA2 | Alternate Function | `MODER` (AF Mode), `AFRL` (AF7) |
| **USART2_RX** | PA3 | Alternate Function | `MODER` (AF Mode), `AFRL` (AF7) |
| **User LED**  | PC13| General Output      | `MODER` (Output Mode) |

---

## 🔍 Code Walkthrough & Register Explanations

### 1. Clock and GPIO Initialization
The clock gates for `GPIOA`, `GPIOC`, and `USART2` are enabled via `RCC` registers. Pins **PA2** and **PA3** are configured to use **Alternate Function 7 (AF7)** for USART2 routing:
```c
RCC->AHB1ENR |= (0x1UL << 0);   // Enable GPIOA Clock
RCC->AHB1ENR |= (0x1UL << 2);   // Enable GPIOC Clock
RCC->APB1ENR |= (0x1UL << 17);  // Enable USART2 Clock

GPIOA->MODER |= (2UL << (2*2) | 2UL << (3*2)); // PA2 & PA3 as Alternate Function
GPIOA->AFRL  |= (0x7UL << (2*4) | 0x7UL << (3*4)); // Route to AF7 (USART2)
```

### 2. USART2 Configuration
The frame format is configured as **8 Data Bits, 1 Stop Bit, No Parity** (`M=0`, `PCE=0`, `STOP=00`). The Baud Rate Register is loaded for 9600 baud, and finally, Transmitter (`TE`), Receiver (`RE`), and the peripheral itself (`UE`) are enabled:
```c
USART2->BRR = 0x0683; // 9600 Baud @ 16MHz
USART2->CR1 |= ((1UL << 2) | (1UL << 3)); // TE=1, RE=1
USART2->CR1 |= (1UL << 13); // UE=1 (Enable USART2)
```

### 3. Error-Aware Polling Loop
The `for(;;)` loop implements an advanced polling mechanism that checks for hardware-level communication errors before processing the byte:
*   **RXNE (Bit 5):** Waits until the Read Data Register is not empty.
*   **Error Checking:** Inspects `SR` for **Overrun (ORE)**, **Noise (NE)**, **Framing (FE)**, or **Parity (PE)** errors. If the byte is corrupt, it is discarded safely.
*   **TXE (Bit 7) & TC (Bit 6):** Waits for the transmit buffer to empty, writes the byte back to `DR`, and explicitly waits for the **Transmission Complete (TC)** flag before clearing it manually (`USART2->SR &= ~(1UL << 6);`).


