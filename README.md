# Building a Community Environmental Vibration & Infrasound Monitoring Network

### A Low-Cost Open Hardware Approach to Understanding Low-Frequency Noise Around Industrial Sites

---

## Introduction: Why This System Exists

Across many communities near large industrial facilities—especially modern high-density computing infrastructure like data centers—residents increasingly report a similar pattern of experiences:

* Persistent low-frequency hums
* Nighttime pressure sensations in buildings
* Sleep disruption without obvious audible noise sources
* Vibrations that are felt more than heard
* Difficulty capturing the phenomenon using standard noise meters

One of the core challenges is that traditional noise measurement tools are not designed for what people are experiencing. Standard sound level meters typically rely on **A-weighted decibel measurements**, which are optimized for human hearing sensitivity between roughly 20 Hz and 20 kHz. Anything below that range—especially **infrasound (below 20 Hz)**—is often poorly represented or entirely filtered out.

At the same time, modern facilities generate significant low-frequency energy from:

* Industrial HVAC systems
* Cooling towers
* High-power electrical infrastructure
* Backup generators
* Structural vibration from large rotating machinery

These systems operate continuously, often 24/7, and their acoustic footprint behaves differently than typical environmental noise sources.

This project proposes a different approach:

> Instead of relying on a single microphone or commercial noise meter, build a distributed, low-cost sensor network that measures both air pressure fluctuations and structural vibration over time.

The goal is not to replace professional acoustic studies, but to enable communities to observe patterns, correlations, and recurring signatures in their environment.

---

## What This System Actually Measures

This system is built around two physical phenomena:

### 1. Air Pressure Fluctuations (Infrasound Proxy)

Low-frequency sound waves are not “sound” in the conventional sense at the sensor level—they are **pressure oscillations in air**.

To capture these, the system uses a high-resolution barometric pressure sensor. Instead of listening like a microphone, it observes subtle changes in atmospheric pressure over time.

This allows detection of:

* Slow oscillatory pressure waves
* Mechanical cycling of large systems
* Large-scale HVAC or cooling tower harmonics
* Environmental pressure disturbances

### 2. Structural Vibration

Many complaints attributed to “sound” are actually transmitted through physical structures:

* Floors
* Walls
* Window frames
* Building foundations

To capture this, a low-noise accelerometer measures motion in three axes. This reveals:

* Building resonance
* Ground-coupled vibration
* Mechanical vibration transmission
* Structural amplification effects

### 3. Time Correlation

The real power of the system is not individual readings, but **time-based correlation**:

* Does vibration occur at the same time every night?
* Does pressure fluctuation match mechanical cycles?
* Do multiple houses detect the same frequency signature?

This transforms subjective experience into measurable patterns.

---

## System Overview

The system is designed as a simple edge-computing node:

* Collects sensor data at high frequency
* Logs raw values locally
* Optionally performs FFT analysis
* Stores structured time-series data
* Can be networked with other nodes

Each unit operates independently, but when deployed across multiple homes, the system becomes a distributed sensing grid.

---

## Hardware Design Philosophy

The guiding principle of this system is:

> Use cheap, widely available components that are easy to replicate and repair.

A typical node costs between $80 and $150 depending on optional upgrades.

It is intentionally not dependent on proprietary equipment or expensive laboratory instruments.

The selected hardware prioritizes:

* Open documentation
* Arduino/ESP32 compatibility
* I2C and SPI simplicity
* Low power operation
* Community reproducibility

---

## Core Hardware Components

### 1. ESP32 Microcontroller

The ESP32 serves as the central processing unit.

It provides:

* Dual-core processing
* Wi-Fi connectivity
* Sufficient speed for FFT computations
* Low power consumption
* Broad Arduino ecosystem support

It acts as both a data logger and optional network node.

---

### 2. BMP390 Barometric Pressure Sensor

The BMP390 is a high-resolution digital pressure sensor.

It measures:

* Atmospheric pressure changes with high sensitivity
* Slow pressure oscillations that may correspond to infrasound sources

Unlike microphones, it does not rely on acoustic membranes—it directly measures pressure changes in air.

This makes it particularly useful for low-frequency analysis.

---

### 3. ADXL355 Low-Noise Accelerometer

The ADXL355 is a precision MEMS accelerometer designed for low-noise measurements.

It provides:

* Three-axis acceleration data
* High sensitivity to small vibrations
* Stability over long time periods

This sensor is critical for identifying whether disturbances are airborne or structurally transmitted.

---

### 4. MicroSD Storage Module

A standard SPI-based SD card module is used for:

* Continuous data logging
* Offline analysis
* Data portability between researchers or community members

The system logs raw sensor readings in CSV format for compatibility with Python-based analysis tools.

---

## Wiring Overview (Conceptual)

The system uses two communication buses:

### I2C Bus (Pressure Sensor)

Used for BMP390 communication.

### SPI Bus (Accelerometer + SD Card)

Shared bus with separate chip select lines.

The ESP32 coordinates both buses simultaneously.

The design ensures:

* Minimal wiring complexity
* Expandability
* Reliable synchronization between sensors

---

## Data Structure

Each sensor node produces a time-series dataset like:

* Timestamp (milliseconds)
* Pressure (Pascals)
* Acceleration X
* Acceleration Y
* Acceleration Z

This format is intentionally simple so that:

* It can be read by Excel
* It can be processed in Python
* It can be shared across a community network

---

## How the System Works in Practice

### Step 1: Continuous Sampling

The ESP32 samples sensors at a fixed interval (typically 100–200 Hz equivalent timing for vibration analysis).

Each reading captures:

* Instantaneous pressure
* Instantaneous acceleration

### Step 2: Local Storage

Data is written to SD card in real time.

This ensures:

* No data loss during Wi-Fi outages
* Independence from cloud services
* Long-term reliability

### Step 3: Optional FFT Processing

The system can compute Fast Fourier Transforms on buffered data.

This reveals:

* Dominant frequency components
* Harmonic structures
* Repeating mechanical signatures

For example, rotating machinery often produces:

* A fundamental frequency
* Harmonics at multiples of that frequency

### Step 4: Pattern Detection

Over time, the system identifies:

* Repeating cycles
* Nighttime-only activity
* Correlated vibration across multiple nodes

This is where the system becomes scientifically interesting.

---

## Example Use Case Scenario

Imagine a neighborhood near a large industrial facility.

Three residents install nodes in different houses:

* Node A: 200 meters away
* Node B: 500 meters away
* Node C: 900 meters away

Over a week, data reveals:

* A recurring vibration signature at 11.8 Hz
* Strongest at night between 11 PM and 5 AM
* Present across all three nodes simultaneously
* Weakest at the furthest location

This pattern suggests a centralized mechanical source rather than random environmental noise.

The system does not claim causation—it reveals structure in the data.

---

## Why Multi-Sensor Design Matters

A key limitation of traditional sound measurement is that it assumes:

> Everything important is audible and airborne.

This system challenges that assumption by separating:

* Airborne pressure fluctuations
* Structural vibration
* Environmental interference

This separation allows more robust interpretation of environmental conditions.

For example:

* If pressure changes without vibration → airborne source
* If vibration without pressure → structural coupling
* If both occur together → strong mechanical source likely nearby

---

## Networking Multiple Nodes

When multiple sensors are deployed across a community, the system becomes significantly more powerful.

Nodes can:

* Share timestamped data
* Upload FFT summaries
* Build frequency heatmaps
* Compare synchronized measurements

This enables:

* Spatial correlation analysis
* Source proximity estimation
* Event clustering across neighborhoods

In effect, the system becomes a **distributed environmental observatory**.

---

## Limitations and Responsible Interpretation

It is important to understand what this system is and is not.

### It CAN:

* Detect low-frequency patterns
* Identify recurring mechanical cycles
* Correlate vibration across locations
* Provide structured environmental data
* Support community-level observation

### It CANNOT:

* Prove health effects
* Identify specific legal violations
* Replace professional acoustic engineering studies
* Provide regulatory-grade certification

The system is best understood as:

> A community science tool for environmental pattern discovery.

---

## Data Analysis Workflow (High Level)

After data collection, analysis typically follows:

1. Import CSV data
2. Remove sensor drift and DC offset
3. Segment into time windows
4. Apply FFT to each window
5. Generate spectrograms
6. Identify dominant frequency bands
7. Compare across multiple nodes

This produces:

* Frequency heatmaps
* Time-based activity graphs
* Cross-location correlation plots

---

## Why This Approach Works

Traditional monitoring approaches fail in this context because they assume:

* Noise is short-term
* Noise is audible
* Noise is isolated

Industrial low-frequency systems behave differently:

* Continuous operation
* Sub-audible energy
* Large spatial propagation
* Structural coupling into buildings

This system is designed specifically for those conditions.

---

## Future Expansion

This architecture can evolve in several directions:

### 1. Real-Time Dashboard

Live visualization of:

* Frequency spectrum
* Pressure fluctuations
* Multi-node comparison

### 2. GPS Time Synchronization

Allows precise alignment between multiple houses.

### 3. Direction Estimation

Using phase differences between nodes.

### 4. Machine Learning Classification

Identify repeating mechanical signatures automatically.

### 5. PCB Integration

Move from breadboard prototypes to reliable deployable hardware.

---

## Conclusion

This system is not a consumer gadget or a medical device. It is a **distributed environmental sensing framework** designed for community-scale observation of low-frequency physical phenomena.

By combining:

* Pressure sensing
* Structural vibration monitoring
* Time-series logging
* Frequency analysis
* Multi-node correlation

It becomes possible to move from anecdotal reports of “feeling something” to structured, measurable datasets that describe what is happening in the environment over time.

The goal is not to interpret or conclude—but to observe, record, and correlate.

In environments where traditional measurement tools fall short, distributed low-cost sensing provides a new layer of visibility into the physical world.
