# 2.1-channel high-efficiency digital audio system

# Sound Terminal®

Datasheet - production data

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/c6d1695e9d337bde32cdfe7de49b5da50821386a17103d3590148d544874c3fa.jpg)  
PowerSSO-36  
STA350BW with exposed pad down (EPD)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/6c168214d0ac1c24cbde8684af276900012e7ba230b91940501e805b5dc13719.jpg)  
STA350B with exposed pad (or slug) up

# Features

- Wide-range supply voltage

-  $5\mathrm{V}$  to  $26\mathrm{V}$  (operating range)  
- 30 V (absolute maximum rating)

- Four power output configurations

- 2 channels of ternary PWM (stereo mode)  $(2 \times 50 \mathrm{~W}$  into  $6 \Omega$  at  $25 \mathrm{~V})$  
- 3 channels - left, right using binary and LFE using ternary PWM (2.1 mode)  $(2 \times 18 \mathrm{~W} + 1 \times 40 \mathrm{~W}$  into  $2 \times 4 \Omega$ ,  $1 \times 8 \Omega$  at  $25 \mathrm{~V})$  
- 2 channels of ternary PWM (2 x 50 W) + stereo lineage ternary  
1 channel of ternary PWM as mono-BTL (1 x 90 W into 3 Ω at 24.5 V)

- FFX™ 100 dB SNR and dynamic range  
- Selectable 32 to  ${192}\mathrm{{kHz}}$  input sample rates  
-  $I^{2}C$  control with selectable device address  
- Digital gain/attenuation +42 dB to -80 dB with 0.125 dB/step resolution  
- Soft-volume update with programmable ratio  
- Individual channel and master gain/attenuation  
- Two independent DRCs configurable as a dual-band anti-clipper ( $B^{2}DRC$ ) or independent limiters/compressors

- EQ-DRC for DRC based on filtered signals  
Dedicated LFE processing for bass boosting with 0.125 dB/step resolution

Audio presets:

- 15 preset crossover filters  
- 5 preset anti-clipping modes  
- Preset nighttime listening mode

- Individual channel and master soft/hard mute  
- Independent channel volume and DSP bypass  
Automatic zero-detect mute  
Automatic invalid input-detect mute  
-  $I^2 S$  input data interface  
- Input and output channel mapping  
- Up to 8 user-programmable biquads per channel  
- 3 coefficient banks for EQ presets storing with fast recall via I²C interface  
- Extended coefficient dynamic up to -4..4 for easy implementation of high shelf filters  
- Bass/treble tones and de-emphasis control  
- Selectable high-pass filter for DC blocking  
- Advanced AM interference frequency switching and noise suppression modes  
- Selectable high or low bandwidth noise-shaping topologies  
- Selectable clock input ratio  
- 96 kHz internal processing sample rate with quantization error noise shaping for very low cutoff frequency filters  
- Thermal overload and short-circuit protection embedded  
Video apps: 576 x Fs input mode supported  
- Fully compatible with the STA339BW and the STA339BWS

# Contents

# 1 Description 12

1.1 Block diagram 13

# 2 Pin connections 14

2.1 Connection diagram 14  
2.2 Pin description 14

# 3 Electrical specifications 16

3.1 Absolute maximum ratings 16  
3.2 Thermal data 16  
3.3 Recommended operating conditions 17  
3.4 Electrical specifications for the digital section 17  
3.5 Electrical specifications for the power section 18  
3.6 Power-on/off sequence 20

# 4 Characterization curves 21

4.1 Mono parallel BTL characteristics 26

# 5 Serial audio interface 28

5.0.1 Timings 28  
5.0.2 Delay serial clock enable 28  
5.0.3 Channel input mapping 28

# 6 Processing data paths 29

# $\mathsf{I}^2\mathsf{C}$  bus specification 31

7.1 Communication protocol 31

7.1.1 Data transition or change 31  
7.1.2 Start condition 31  
7.1.3 Stop condition 31  
7.1.4 Data input 31

7.2 Device addressing 31  
7.3 Write operation 32

7.3.1 Byte write 32  
7.3.2 Multi-byte write 32

# 7.4 Read operation 32

7.4.1 Current address byte read 32  
7.4.2 Current address multi-byte read 32  
7.4.3 Random address byte read 32  
7.4.4 Random address multi-byte read 32  
7.4.5 Write mode sequence 33  
7.4.6 Read mode sequence 33

# 8 Register description 34

# 8.1 Configuration register A (addr 0x00) 37

8.1.1 Master clock select 37  
8.1.2 Interpolation ratio select 38  
8.1.3 Thermal warning recovery bypass 38  
8.1.4 Thermal warning adjustment bypass 38  
8.1.5 Fault detect recovery bypass 39

# 8.2 Configuration register B (addr 0x01) 39

8.2.1 Serial audio input interface format 39  
8.2.2 Serial data interface 40  
8.2.3 Serial data first bit 40  
8.2.4 Delay serial clock enable 42  
8.2.5 Channel input mapping 42

# 8.3 Configuration register C (addr 0x02) 43

8.3.1 FFX power output mode 43  
8.3.2 FFX compensating pulse size register 43  
8.3.3 Overcurrent warning detect adjustment bypass 44

# 8.4 Configuration register D (addr 0x03) 44

8.4.1 High-pass filter bypass 44  
8.4.2 De-emphasis 44  
8.4.3 DSP bypass 45  
8.4.4 Post-scale link 45  
8.4.5 Biquad coefficient link 45  
8.4.6 Dynamic range compression/anti-clipping bit 45  
8.4.7 Zero-detect mute enable 46  
8.4.8 Submix mode enable 46

8.5 Configuration register E (addr 0x04) 46

8.5.1 Max. power correction variable 46  
8.5.2 Max. power correction 46  
8.5.3 Noise-shaper bandwidth selection 47  
8.5.4 AM mode enable 47  
8.5.5 PWM speed mode 47  
8.5.6 Distortion compensation variable enable 47  
8.5.7 Zero-crossing volume enable 47  
8.5.8 Soft-volume update enable 48

8.6 Configuration register F (addr 0x05) 48

8.6.1 Output configuration 48  
8.6.2 Invalid input detect mute enable 54  
8.6.3 Binary output mode clock loss detection 54  
8.6.4 LRCK double trigger protection 54  
8.6.5 Auto EAPD on clock loss 54  
8.6.6 IC power-down 54  
8.6.7 External amplifier power-down 55

8.7 Volume control registers (addr 0x06 - 0x0A) 55

8.7.1 Mute/line output configuration register 55  
8.7.2 Master volume register 55  
8.7.3 Channel 1 volume 55  
8.7.4 Channel 2 volume 56  
8.7.5 Channel 3 / line output volume 56

8.8 Audio preset registers (addr 0x0B and 0x0C) 57

8.8.1 Audio preset register 1 (addr 0x0B) 57  
8.8.2 Audio preset register 2 (addr 0x0C) 58  
8.8.3 AM interference frequency switching 58  
8.8.4 Bass management crossover 58

8.9 Channel configuration registers (addr 0x0E - 0x10) 59

8.9.1 Tone control bypass 59  
8.9.2 EQ bypass 59  
8.9.3 Volume bypass 60  
8.9.4 Binary output enable registers 60  
8.9.5 Limiter select 60  
8.9.6 Output mapping 60

8.10 Tone control register (addr 0x11) 61

8.10.1 Tone control 61  
8.11 Dynamic control registers (addr 0x12 - 0x15) 61  
8.11.1 Limiter 1 attack/release rate 61  
8.11.2 Limiter 1 attack/release threshold 61  
8.11.3 Limiter 2 attack/release rate 61  
8.11.4 Limiter 2 attack/release threshold 62  
8.11.5 Limiter 1 extended attack threshold (addr 0x32) 65  
8.11.6 Limiter 1 extended release threshold (addr 0x33) 65  
8.11.7 Limiter 2 extended attack threshold (addr 0x34 .) 66  
8.11.8 Limiter 2 extended release threshold (addr 0x35) 66

8.12 User-defined coefficient control registers (addr 0x16 - 0x26) 66

8.12.1 Coefficient address register 66  
8.12.2 Coefficient b1 data register bits 23:16 66  
8.12.3 Coefficient b1 data register bits 15:8 66  
8.12.4 Coefficient b1 data register bits 7:0 66  
8.12.5 Coefficient b2 data register bits 23:16 67  
8.12.6 Coefficient b2 data register bits 15:8 67  
8.12.7 Coefficient b2 data register bits 7:0 67  
8.12.8 Coefficient a1 data register bits 23:16 67  
8.12.9 Coefficient a1 data register bits 15:8 67  
8.12.10 Coefficient a1 data register bits 7:0 67  
8.12.11 Coefficient a2 data register bits 23:16 67  
8.12.12 Coefficient a2 data register bits 15:8 68  
8.12.13 Coefficient a2 data register bits 7:0 68  
8.12.14 Coefficient b0 data register bits 23:16 68  
8.12.15 Coefficient b0 data register bits 15:8 68  
8.12.16 Coefficient b0 data register bits 7:0 68  
8.12.17 Coefficient write/read control register 68  
8.12.18 User-defined EQ 71  
8.12.19 Pre-scale 71  
8.12.20 Post-scale 71  
8.12.21 Overcurrent post-scale 72

8.13 Variable max. power correction registers (addr 0x27 - 0x28) 73  
8.14 Variable distortion compensation registers (addr 0x29 - 0x2A) 73  
8.15 Fault detect recovery constant registers (addr 0x2B - 0x2C) 74  
8.16 Device status register (addr 0x2D) 74

8.17 EQ coefficients and DRC configuration register (addr 0x31) 75  
8.18 Extended configuration register (addr 0x36) 76

8.18.1 Dual-band DRC 76  
8.18.2 EQ DRC mode 77  
8.18.3 Extended post-scale range 78  
8.18.4 Extendedattack rate 78  
8.18.5 Extended biquad selector 79

8.19 EQ soft-volume configuration registers (addr 0x37 - 0x38) 79  
8.20 DRC RMS filter coefficients (addr 0x39-0x3E) 80  
8.21 Extra volume resolution configuration registers (address 0x3F) 81  
8.22 Quantization error noise correction (address 0x48) 82  
8.23 Extended coefficient range up to -4...4 (address 0x49, 0x4A) 83  
8.24 Miscellaneous registers (address 0x4B, 0x4C) 84

8.24.1 Rate powerdown enable (RPDNEN) bit (address 0x4B, bit D7) ..... 84  
8.24.2 Noise-shaping on DC cut filter enable (NSHHPEN) bit (address 0x4B, bit D6) 84  
8.24.3 Bridge immediate off (BRIDGOFF) bit (address 0x4B, bit D5) 84  
8.24.4 Channel PWM enable (CPWMEN) bit (address 0x4B, bit D2) 85  
8.24.5 Power-down delay selector (PNDLSL[2:0]) bits (address 0x4C, bit D4, D3, D2) 85

9 PowerSSO-36 slug-down package thermal characteristics (STA350BW) 86  
10 Package information 87  
11 Ordering information 92  
12 Revision history 93

# List of tables

Table 1. Pin description 14

Table 2. Absolute maximum ratings 16

Table 3. Thermal data. 16

Table 4. Recommended operating conditions 17

Table 5. Electrical specifications - digital section 17

Table 6. Electrical specifications - power section 18

Table 7. Timing parameters for slave mode 28

Table 8. Register summary.. 34

Table 9. Master clock select. 37

Table 10. Input sampling rates 37

Table 11. Internal interpolation ratio 38

Table 12. IR bit settings as a function of input sample rate 38

Table 13. Thermal warning recovery bypass 38

Table 14. Thermal warning adjustment bypass 38

Table 15. Fault detect recovery bypass 39

Table 16. Serial audio input interface 39

Table 17. Serial data first bit. 40

Table 18. Support serial audio input formats for MSB-first (SAIFB = 0). 40

Table 19. Supported serial audio input formats for LSB-first (SAIFB = 1) 41

Table 20. Delay serial clock enable 42

Table 21. Channel input mapping. 42

Table 22. FFX power output mode 43

Table 23. Output modes 43

Table 24. FFX compensating pulse size bits 43

Table 25. Compensating pulse size 43

Table 26. Overcurrent warning bypass. 44

Table 27. High-pass filter bypass 44

Table 28. De-emphasis. 44

Table 29. DSP bypass 45

Table 30. Post-scale link. 45

Table 31. Biquad coefficient link. 45

Table 32. Dynamic range compression/anti-clipping bit 45

Table 33. Zero-detect mute enable. 46

Table 34. Sub-mix mode enable.. 46

Table 35. Max. power correction variable. 46

Table 36. Max. power correction 46

Table 37. Noise-shaper bandwidth selection 47

Table 38. AM mode enable. 47

Table 39. PWM speed mode 47

Table 40. Distortion compensation variable enable 47

Table 41. Zero-crossing volume enable . 47

Table 42. Soft-volume update enable. 48

Table 43. Output configuration 48

Table 44. Output configuration engine selection 48

Table 45. Invalid input detect mute enable. 54

Table 46. Binary output mode clock loss detection 54

Table 47. LRCK double trigger protection 54

Table 48. Auto EAPD on clock loss 54

Table 49. IC power-down 54  
Table 50. External amplifier power-down 55  
Table 51. Line output configuration 55  
Table 52. Master volume offset as a function of MV[7:0] 56  
Table 53. Channel volume as a function of CxV[7:0] 57  
Table 54. Audio preset gain compression/limiters selection for AMGC[3:2] = 00. 57  
Table 55. AM interference frequency switching bits 58  
Table 56. Audio preset AM switching frequency selection 58  
Table 57. Bass management crossover 58  
Table 58. Bass management crossover frequency 58  
Table 59. Tone control bypass 59  
Table 60. EQ bypass 60  
Table 61. Binary output enable registers 60  
Table 62. Channel limiter mapping as a function of CxLS bits 60  
Table 63. Channel output mapping as a function of CxOM bits 60  
Table 64. Tone control boost/cut as a function of BTC and TTC bits. 61  
Table 65. Limiter attack rate as a function of LxA bits 63  
Table 66. Limiter release rate as a function of LxR bits 63  
Table 67. Limiter attack threshold as a function of LxAT bits (AC-mode). 64  
Table 68. Limiter release threshold as a function of LxRT bits (AC-mode) 64  
Table 69. Limiter attack threshold as a function of LxAT bits (DRC -mode) 65  
Table 70. Limiter release threshold as a as a function of LxRT bits (DRC-mode) 65  
Table 71. RAM block for biquads, mixing, scaling and bass management. 72  
Table 72. Status register bits 74  
Table 73. EQ RAM select . 75  
Table 74. Anti-clipping and DRC preset 75  
Table 75. Anti-clipping selection for AMGC[3:2] = 01 . 75  
Table 76. Biquad filter settings 83  
Table 77. PowerSSO-36 EPD mechanical data 88  
Table 78. PowerSSO36 exposed pad up mechanical data 90  
Table 79. Order code 92  
Table 80. Document revision history 93

# List of figures

Figure 1. Block diagram 13  
Figure 2. Pin connection PowerSSO-36 (top view for STA350BW, bottom view for STA350B) . . . 14  
Figure 3. Test circuit 19  
Figure 4. Power-on sequence 20  
Figure 5. Power-off sequence for pop-free turn-off 20  
Figure 6. Demonstration board, 2.0 channels 21  
Figure 7. Mono parallel BTL schematic 22  
Figure 8. THD+N vs. output power  $(\mathrm{V}_{\mathrm{CC}} = 25\mathrm{~V},\mathrm{load} = 6\Omega)$  23  
Figure 9. THD+N vs. output power  $(\mathrm{V}_{\mathrm{CC}} = 18\mathrm{~V},\mathrm{load} = 8\Omega)$  23  
Figure 10. Output power vs.  $V_{CC}$  (load = 6 Ω). 24  
Figure 11. Output power vs.  $V_{CC}$  (load = 8 Ω). 24  
Figure 12. Efficiency vs. output power  $(\mathrm{V}_{\mathrm{CC}} = 25\mathrm{~V},\mathrm{load} = 6\Omega)$  25  
Figure 13. Efficiency vs. output power  $(V_{CC} = 25\mathrm{V},\mathrm{load} = 8\Omega)$  25  
Figure 14. THD+N vs. output power  $(V_{CC} = 25\mathrm{~V}, \text{load} = 3\Omega)$  26  
Figure 15. Output power vs.  $V_{CC}$  (load = 3 Ω). 26  
Figure 16. Efficiency vs. output power  $(\mathrm{V_{CC}} = 26\mathrm{V},\mathrm{load} = 3\Omega)$  27  
Figure 17. Efficiency vs. output power  $(\mathrm{V}_{\mathrm{CC}} = 18\mathrm{~V},\mathrm{load} = 3\Omega)$  27  
Figure 18. Timing diagram for SAI interface 28  
Figure 19. Left and right processing - part 1 29  
Figure 20. Processing - part 2 30  
Figure 21. Write mode sequence. 33  
Figure 22. Read mode sequence. 33  
Figure 23. OCFG = 00 (default value) 49  
Figure 24. OCFG = 01 49  
Figure 25. OCFG = 10 49  
Figure 26. OCFG = 11 50  
Figure 27. Output mapping scheme 50  
Figure 28. 2.0 channels (OCFG = 00) PWM slots 51  
Figure 29. 2.1 channels (OCFG = 01) PWM slots 52  
Figure 30. 2.1 channels (OCFG = 10) PWM slots 53  
Figure 31. Basic limiter and volume flow diagram 63  
Figure 32.  $\mathbf{B}^2\mathbf{D}\mathbf{R}\mathbf{C}$  scheme 76  
Figure 33. EQDRC scheme 78  
Figure 34. Extra resolution volume scheme. 81  
Figure 35. Biquad filter structure with quantization error noise-shaping 83  
Figure 36. Double-layer PCB with 2 copper ground areas and 24 via holes 86  
Figure 37. PowerSSO-36 power derating curve 86  
Figure 38. PowerSSO-36 EPD package outline 88  
Figure 39. PowerSSO36 (slug-up) package outline. 90

# List of tables

Table 1. Pin description 14

Table 2. Absolute maximum ratings 16

Table 3. Thermal data. 16

Table 4. Recommended operating conditions 17

Table 5. Electrical specifications - digital section 17

Table 6. Electrical specifications - power section 18

Table 7. Timing parameters for slave mode 28

Table 8. Register summary.. 34

Table 9. Master clock select. 37

Table 10. Input sampling rates 37

Table 11. Internal interpolation ratio 38

Table 12. IR bit settings as a function of input sample rate 38

Table 13. Thermal warning recovery bypass 38

Table 14. Thermal warning adjustment bypass 38

Table 15. Fault detect recovery bypass 39

Table 16. Serial audio input interface 39

Table 17. Serial data first bit. 40

Table 18. Support serial audio input formats for MSB-first (SAIFB = 0). 40

Table 19. Supported serial audio input formats for LSB-first (SAIFB = 1) 41

Table 20. Delay serial clock enable 42

Table 21. Channel input mapping. 42

Table 22. FFX power output mode 43

Table 23. Output modes 43

Table 24. FFX compensating pulse size bits 43

Table 25. Compensating pulse size 43

Table 26. Overcurrent warning bypass. 44

Table 27. High-pass filter bypass 44

Table 28. De-emphasis. 44

Table 29. DSP bypass 45

Table 30. Post-scale link. 45

Table 31. Biquad coefficient link. 45

Table 32. Dynamic range compression/anti-clipping bit 45

Table 33. Zero-detect mute enable.. 46

Table 34. Sub-mix mode enable.. 46

Table 35. Max. power correction variable. 46

Table 36. Max. power correction 46

Table 37. Noise-shaper bandwidth selection 47

Table 38. AM mode enable. 47

Table 39. PWM speed mode 47

Table 40. Distortion compensation variable enable 47

Table 41. Zero-crossing volume enable . 47

Table 42. Soft-volume update enable. 48

Table 43. Output configuration 48

Table 44. Output configuration engine selection 48

Table 45. Invalid input detect mute enable. 54

Table 46. Binary output mode clock loss detection 54

Table 47. LRCK double trigger protection 54

Table 48. Auto EAPD on clock loss 54

Table 49. IC power-down 54

Table 50. External amplifier power-down 55

Table 51. Line output configuration 55

Table 52. Master volume offset as a function of MV[7:0] 56

Table 53. Channel volume as a function of CxV[7:0] 57

Table 54. Audio preset gain compression/limiters selection for AMGC[3:2] = 00. 57

Table 55. AM interference frequency switching bits 58

Table 56. Audio preset AM switching frequency selection 58

Table 57. Bass management crossover 58

Table 58. Bass management crossover frequency 58

Table 59. Tone control bypass 59

Table 60. EQ bypass 60

Table 61. Binary output enable registers 60

Table 62. Channel limiter mapping as a function of CxLS bits 60

Table 63. Channel output mapping as a function of CxOM bits 60

Table 64. Tone control boost/cut as a function of BTC and TTC bits. 61

Table 65. Limiter attack rate as a function of LxA bits 63

Table 66. Limiter release rate as a function of LxR bits 63

Table 67. Limiter attack threshold as a function of LxAT bits (AC-mode). 64

Table 68. Limiter release threshold as a function of LxRT bits (AC-mode) 64

Table 69. Limiter attack threshold as a function of LxAT bits (DRC -mode) 65

Table 70. Limiter release threshold as a as a function of LxRT bits (DRC-mode) 65

Table 71. RAM block for biquads, mixing, scaling and bass management. 72

Table 72. Status register bits 74

Table 73. EQ RAM select . 75

Table 74. Anti-clipping and DRC preset 75

Table 75. Anti-clipping selection for AMGC[3:2] = 01 . 75

Table 76. Biquad filter settings 83

Table 77. PowerSSO-36 EPD mechanical data 88

Table 78. PowerSSO36 exposed pad up mechanical data 90

Table 79. Order code 92

Table 80. Document revision history 93

# 1 Description

The STA350Bx is an integrated solution of digital audio processing, digital amplifier control, and FFX-power output stage, thereby creating a high-power single-chip  $\mathsf{FFX}^{\mathsf{TM}}$  solution comprising high-quality, high-efficiency, and all-digital amplification.

The STA350Bx is based on an FFX (fully flexible amplification) processor, a proprietary technology from STMicroelectronics. FFX is the evolution and the enlargement of ST's ternary technology: the new processor can be configured to work in ternary, binary, binary differential and phase-shift PWM modulation schemes.

The STA350Bx contains the ternary, binary and binary differential implementations, a subset of the full capability of the FFX processor.

The STA350Bx is part of the Sound Terminal® family that provides full digital audio streaming to the speaker, offering cost effectiveness, low power dissipation and sound enrichment.

The STA350Bx power section consists of four independent half-bridges. These can be configured via digital control to operate in different modes. 2.1 channels can be provided by two half-bridges and a single full-bridge, providing up to  $2 \times 18\mathrm{W} + 1 \times 40\mathrm{W}$  of music output power, by using standard 4 and  $8\Omega$  speakers. Two channels can be provided by two full-bridges, providing up to  $2 \times 50\mathrm{W}$  of music power, by using standard  $6\Omega$  speaker or  $2 \times 40\mathrm{W}$  by using  $8\Omega$  speakers at  $25\mathrm{V}$ . The IC can also be configured as 2.1 channels with  $2 \times 40\mathrm{W}$  provided by the device and external power for FFX power drive. If configured as mono-BTL, the latter is capable of providing up to  $1 \times 90\mathrm{W}$  on a standard  $3\Omega$  load or  $1 \times 75\mathrm{W}$  by using a  $4\Omega$ , setting the supply voltage at  $25\mathrm{V}$ . Please refer to the package thermal characteristics and application suggestions for more details.

Also provided in the STA350Bx are a full assortment of digital processing features. This includes up to 8 programmable biquads (EQ) per channel. Special digital signal processing techniques are available in order to manage low-frequency quantization noise in case of very low frequency cutoff filter thresholds. The coefficient range -4..4 allows the easy implementation of high shelf filters. Available presets allow the advantage of earlier time-market by substantially reducing the amount of software development needed for certain functions. This includes audio preset volume loudness, preset volume curves and preset EQ settings. There are also new advanced AM radio interference reduction modes. Dual-band DRC dynamically equalizes the system to provide speaker linear frequency response regardless of output power level. This feature independently processes the two bands, controlling dynamically the output power level in each band and so providing better sound clarity.

The serial audio data input interface accepts all possible formats, including the popular I²S format. Three channels of FFX processing are provided. This high-quality conversion from PCM audio to FFX PWM switching waveform provides over 100 dB SNR and dynamic range.

# 1.1 Block diagram

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/dd5d0a8c659c1c8b7011d67986ecc9a1a5e54b83372f69fd11ae765f12ce1c3a.jpg)  
Figure 1. Block diagram

# 2 Pin connections

# 2.1 Connection diagram

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/3c3907200b0837ab7ebc91c40d05bb1a85360fe5b4ab409fd27977b076d68e7f.jpg)  
Figure 2. Pin connection PowerSSO-36 (top view for STA350BW, bottom view for STA350B)

# 2.2 Pin description

Table 1. Pin description  

<table><tr><td>Pin</td><td>Type</td><td>Name</td><td>Description</td></tr><tr><td>1</td><td>GND</td><td>GND_SUB</td><td>Substrate ground</td></tr><tr><td>2</td><td>I</td><td>SA</td><td>I²C select address (pull-down)</td></tr><tr><td>3</td><td>I</td><td>TEST_MODE</td><td>This pin must be connected to ground (pull-down)</td></tr><tr><td>4</td><td>I/O</td><td>VSS</td><td>Internal reference at Vcc-3.3 V</td></tr><tr><td>5</td><td>I/O</td><td>VCC_REG</td><td>Internal Vcc reference</td></tr><tr><td>6</td><td>O</td><td>OUT2B</td><td>Output half-bridge 2B</td></tr><tr><td>7</td><td>GND</td><td>GND2</td><td>Power negative supply</td></tr><tr><td>8</td><td>Power</td><td>VCC2</td><td>Power positive supply</td></tr><tr><td>9</td><td>O</td><td>OUT2A</td><td>Output half-bridge 2A</td></tr></table>

Table 1. Pin description (continued)  

<table><tr><td>Pin</td><td>Type</td><td>Name</td><td>Description</td></tr><tr><td>10</td><td>O</td><td>OUT1B</td><td>Output half-bridge 1B</td></tr><tr><td>11</td><td>Power</td><td>VCC1</td><td>Power positive supply</td></tr><tr><td>12</td><td>GND</td><td>GND1</td><td>Power negative supply</td></tr><tr><td>13</td><td>O</td><td>OUT1A</td><td>Output half-bridge 1A</td></tr><tr><td>14</td><td>GND</td><td>GND_REG</td><td>Internal ground reference</td></tr><tr><td>15</td><td>Power</td><td>VDD</td><td>Internal 3.3 V reference voltage</td></tr><tr><td>16</td><td>I</td><td>CONFIG</td><td>Parallel mode command</td></tr><tr><td>17</td><td>O</td><td>OUT3B/FFX3B</td><td>PWM out CH3B / external bridge driver</td></tr><tr><td>18</td><td>O</td><td>OUT3A/FFX3A</td><td>PWM out CH3A / external bridge driver</td></tr><tr><td>19</td><td>O</td><td>EAPD/OUT4B</td><td>Power-down for external bridge / PWM out CH4B</td></tr><tr><td>20</td><td>I/O</td><td>TWARN/OUT4A</td><td>Thermal warning from external bridge (pull-up when input) / PWM out CH4A</td></tr><tr><td>21</td><td>Power</td><td>VDD_DIG</td><td>Digital supply voltage</td></tr><tr><td>22</td><td>GND</td><td>GND_DIG</td><td>Digital ground</td></tr><tr><td>23</td><td>I</td><td>PWRDN</td><td>Power down (pull-up)</td></tr><tr><td>24</td><td>Power</td><td>VDD_PLL</td><td>Positive supply for PLL</td></tr><tr><td>25</td><td>I</td><td>FILTER_PLL</td><td>Connection to PLL filter</td></tr><tr><td>26</td><td>GND</td><td>GND_PLL</td><td>Negative supply for PLL</td></tr><tr><td>27</td><td>I</td><td>XTI</td><td>PLL input clock</td></tr><tr><td>28</td><td>I</td><td>BICKI</td><td>I²S serial clock</td></tr><tr><td>29</td><td>I</td><td>LRCKI</td><td>I²S left/right clock</td></tr><tr><td>30</td><td>I</td><td>SDI</td><td>I²S serial data channels 1 and 2</td></tr><tr><td>31</td><td>I</td><td>RESET</td><td>Reset (pull-up)</td></tr><tr><td>32</td><td>O</td><td>INTLine</td><td>Fault interrupt</td></tr><tr><td>33</td><td>I/O</td><td>SDA</td><td>I²C serial data</td></tr><tr><td>34</td><td>I</td><td>SCL</td><td>I²C serial clock</td></tr><tr><td>35</td><td>GND</td><td>GND_DIG</td><td>Digital ground</td></tr><tr><td>36</td><td>Power</td><td>VDD_DIG</td><td>Digital supply voltage</td></tr></table>

# 3 Electrical specifications

# 3.1 Absolute maximum ratings

Table 2. Absolute maximum ratings  

<table><tr><td>Symbol</td><td>Parameter</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td>Vcc</td><td>Power supply voltage (VCCxA, VCCxB)</td><td>-0.3</td><td></td><td>30</td><td>V</td></tr><tr><td>VDD_DIG</td><td>Digital supply voltage</td><td>-0.3</td><td></td><td>4</td><td>V</td></tr><tr><td>VDD_PLL</td><td>PLL supply voltage</td><td>-0.3</td><td></td><td>4</td><td></td></tr><tr><td>Top</td><td>Operating junction temperature</td><td>-20</td><td></td><td>150</td><td>°C</td></tr><tr><td>Tstg</td><td>Storage temperature</td><td>-40</td><td></td><td>150</td><td>°C</td></tr></table>

Warning: Stresses beyond those listed in Table 2 above may cause permanent damage to the device. These are stress ratings only, and functional operation of the device at these or any other conditions beyond those indicated under "Recommended operating conditions" are not implied. Exposure to AMR conditions for extended periods may affect device reliability. In the real application, power supplies with nominal values rated within the recommended operating conditions may rise beyond the maximum operating conditions for a short time when no or very low current is sunk (amplifier in mute state). In this case the reliability of the device is guaranteed, provided that the absolute maximum ratings are not exceeded.

# 3.2 Thermal data

Table 3. Thermal data  

<table><tr><td>Symbol</td><td>Parameter</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td>Rthj-case</td><td>Thermal resistance junction-case (thermal pad)</td><td></td><td></td><td>1.5</td><td>°C/W</td></tr><tr><td>Tthsdj</td><td>Thermal shutdown junction temperature</td><td></td><td>150</td><td></td><td>°C</td></tr><tr><td>Tth-w</td><td>Thermal warning temperature</td><td></td><td>130</td><td></td><td>°C</td></tr><tr><td>Tth-sdh</td><td>Thermal shutdown hysteresis</td><td></td><td>20</td><td></td><td>°C</td></tr><tr><td>Rthj-amb</td><td colspan="5">Thermal resistance junction-ambient (1)</td></tr></table>

1. See Section 9: PowerSSO-36 slug-down package thermal characteristics (STA350BW) on page 86 for details.

# 3.3 Recommended operating conditions

Table 4. Recommended operating conditions  

<table><tr><td>Symbol</td><td>Parameter</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td>Vcc</td><td>Power supply voltage (VCCxA, VCCxB)</td><td>5</td><td></td><td>26</td><td>V</td></tr><tr><td>VDD_DIG</td><td>Digital supply voltage</td><td>2.7</td><td>3.3</td><td>3.6</td><td>V</td></tr><tr><td>VDD_PLL</td><td>PLL supply voltage</td><td>2.7</td><td>3.3</td><td>3.6</td><td>V</td></tr><tr><td>Tamb</td><td>Ambient temperature</td><td>-20</td><td></td><td>+85</td><td>°C</td></tr></table>

# 3.4 Electrical specifications for the digital section

Table 5. Electrical specifications - digital section  

<table><tr><td>Symbol</td><td>Parameter</td><td>Conditions</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td>Iil</td><td>Low-level input current without pull-up/down device</td><td>Vi = 0 V</td><td></td><td>1</td><td>5</td><td>μA</td></tr><tr><td>Iih</td><td>High-level input current without pull-up/down device</td><td>Vi = VDD_DIG = 3.6 V</td><td></td><td>1</td><td>5</td><td>μA</td></tr><tr><td>Vil</td><td>Low-level input voltage</td><td></td><td></td><td></td><td>0.2* VDD_DIG</td><td>V</td></tr><tr><td>Vih</td><td>High-level input voltage</td><td></td><td>0.8* VDD_DIG</td><td></td><td></td><td>V</td></tr><tr><td>Vol</td><td>Low-level output voltage</td><td>Iol=2 mA</td><td></td><td></td><td>0.4* VDD_DIG</td><td>V</td></tr><tr><td>Voh</td><td>High-level output voltage</td><td>Ioh=2 mA</td><td>0.8* VDD_DIG</td><td></td><td></td><td>V</td></tr><tr><td>Ipu</td><td>Pull-up/down current</td><td></td><td>25</td><td>66</td><td>125</td><td>μA</td></tr><tr><td>Rpu</td><td>Equivalent pull-up/down resistance</td><td></td><td></td><td>50</td><td></td><td>kΩ</td></tr></table>

# 3.5 Electrical specifications for the power section

The specifications given in this section are valid for the operating conditions:  $V_{CC} = 24 \, \text{V}$ ,  $f = 1 \, \text{kHz}$ ,  $f_{sw} = 384 \, \text{kHz}$ ,  $T_{amb} = 25^{\circ} \, \text{C}$  and  $R_L = 8 \, \Omega$ , unless otherwise specified.

Table 6. Electrical specifications - power section  

<table><tr><td>Symbol</td><td>Parameter</td><td>Conditions</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td rowspan="4">Po</td><td rowspan="2">Continuous output power, BTL, ternary mode</td><td>THD = 1%</td><td></td><td>27</td><td></td><td rowspan="2">W</td></tr><tr><td>THD = 10%</td><td></td><td>36</td><td></td></tr><tr><td rowspan="2">Continuous output power SE, binary mode, RL = 4 Ω</td><td>THD = 1%</td><td></td><td>12</td><td></td><td rowspan="2">W</td></tr><tr><td>THD = 10%</td><td></td><td>15.5</td><td></td></tr><tr><td>RdsON</td><td>Power P-channel/N-channel MOSFET (total bridge)</td><td>Id = 1.5 A</td><td></td><td>180</td><td>250</td><td>mΩ</td></tr><tr><td>Idss</td><td>Power P-channel/N-channel leakage</td><td>VCC = 20 V</td><td></td><td></td><td>10</td><td>μA</td></tr><tr><td>ILDT</td><td>Low current dead time (static)</td><td>Resistive load(1)</td><td></td><td>8</td><td>15</td><td>ns</td></tr><tr><td>IHDT</td><td>High current dead time (dynamic)</td><td>I load(1) = 1.5 A</td><td></td><td>15</td><td>30</td><td>ns</td></tr><tr><td>tr</td><td>Rise time</td><td>Resistive load(1)</td><td></td><td>10</td><td>18</td><td>ns</td></tr><tr><td>tf</td><td>Fall time</td><td>Resistive load(1)</td><td></td><td>10</td><td>18</td><td>ns</td></tr><tr><td>Vcc</td><td>Supply voltage operating voltage</td><td></td><td>5</td><td></td><td>26</td><td>V</td></tr><tr><td rowspan="2">Ivcc</td><td>Supply current from Vcc in power-down</td><td>PWRDN = 0</td><td></td><td>1</td><td></td><td>μA</td></tr><tr><td>Supply current from Vcc in operation</td><td>PCM input signal = -60 dBfs, Switching frequency = 384 kHz, No LC filters</td><td></td><td>52</td><td>60</td><td>mA</td></tr><tr><td>Ivdd</td><td>Supply current FFX processing (reference only)</td><td>Internal clock = 49.152 MHz</td><td></td><td>55</td><td>70</td><td>mA</td></tr><tr><td>Ilim</td><td>Overcurrent limit</td><td>(2)</td><td>3.0</td><td>3.8</td><td>4.0</td><td>A</td></tr><tr><td>Isc</td><td>Short-circuit protection</td><td>Hi-Z output</td><td>4.0</td><td>5.0</td><td></td><td>A</td></tr><tr><td>UVL</td><td>Undervoltage protection</td><td></td><td></td><td></td><td>4.3</td><td>V</td></tr><tr><td>OVP</td><td>Overvoltage protection</td><td></td><td></td><td>29</td><td></td><td>V</td></tr><tr><td>tmin</td><td>Output minimum pulse width</td><td>No load</td><td></td><td>100</td><td></td><td>ns</td></tr><tr><td>DR</td><td>Dynamic range</td><td></td><td></td><td>100</td><td></td><td>dB</td></tr><tr><td rowspan="2">SNR</td><td>Signal-to-noise ratio, ternary mode</td><td>A-Weighted</td><td></td><td>100</td><td></td><td>dB</td></tr><tr><td>Signal-to-noise ratio binary mode</td><td></td><td></td><td>90</td><td></td><td>dB</td></tr><tr><td>THD+N</td><td>Total harmonic distortion + noise</td><td>FFX stereo mode, Po = 1 W f = 1 kHz</td><td></td><td>0.09</td><td></td><td>%</td></tr></table>

Table 6. Electrical specifications - power section (continued)  

<table><tr><td>Symbol</td><td>Parameter</td><td>Conditions</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td>XTALK</td><td>Crosstalk</td><td>FFX stereo mode, &lt;5 kHz One channel driven at 1 W Other channel measured</td><td></td><td>80</td><td></td><td>dB</td></tr><tr><td>PSRR</td><td>Power Supply Rejection Ratio</td><td>FFX stereo mode, &lt;5 kHz VRipple01V RMS Audio input = dither only</td><td></td><td>80</td><td></td><td>dB</td></tr><tr><td rowspan="2">η</td><td>Peak efficiency, FFX mode</td><td>Po = 2 x 25 W into 8 Ω</td><td></td><td>90</td><td></td><td rowspan="2">%</td></tr><tr><td>Peak efficiency, binary modes</td><td>Po = 2 x 10W into 4 Ω + 1 x 20W into 8 Ω</td><td></td><td>86</td><td></td></tr></table>

1. Refer to Figure 3: Test circuit.  
2. Limit current if the register (OCRB Section 8.3.3) overcurrent warning detect adjustment bypass is enabled. When disabled refer to the Isc.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/f4479d2d5e216fda7c704f55c3833e8e64939ab4c0c891bbb321fcb6c341ad12.jpg)  
Figure 3. Test circuit

# 3.6 Power-on/off sequence

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/50e2b5268b1e4218090d2df53969b68304d53b2b8656b32ab9cc6ce0c5c9af42.jpg)  
Figure 4. Power-on sequence

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/db48b049c9c29b4d4d391b67964b68359e9132ba8d4f8d964d45e62ee0cb93f9.jpg)  
Figure 5. Power-off sequence for pop-free turn-off

# 4 Characterization curves

The following characterization curves have been made using the STA350Bx demonstration board with 2.0 channels (refer to the schematic in Figure 8) under the following test conditions:

$V_{CC} = 25\mathrm{~V}$ ,  $f = 1\mathrm{kHz}$ ,  $f_{SW} = 384\mathrm{kHz}$ ,  $\mathrm{Tamb} = 25^{\circ}\mathrm{C}$  and  $\mathrm{RL} = 6\Omega$ , unless otherwise specified.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/ad3ced8fdec4cf23aa70c84981fd3889bdede523d0768ca85fbe15bdf94e4356.jpg)  
Figure 6. Demonstration board, 2.0 channels

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/eba4570fcce592d246ab2e873902884a95c76f445f05eb99778e5ba5e97c8f17.jpg)  
Figure 7. Mono parallel BTL schematic

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/8f59a1abd3e723c86c9480130b3d23489f9a2d9fce96e9ac8c30894a30f160fb.jpg)  
Figure 8. THD+N vs. output power (VCC = 25 V, load = 6 Ω)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/61350ac7fedd766febccf3bf276d59391a7b4a0e3287f1e9216d8aeda5ea930b.jpg)  
Figure 9. THD+N vs. output power (VCC = 18 V, load = 8 Ω)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/0eb43db33df505fe3dfdc8e84896427f096aa6e19022b6d86cf03917b96d190f.jpg)  
Figure 10. Output power vs.  $V_{CC}$  (load = 6 Ω)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/2099ece7f5e91a8734c83a5e330f798447299145c27e7d315b812bb6a51ca694.jpg)  
Figure 11. Output power vs.  $V_{CC}$  (load = 8 Ω)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/64404ad0cbe76eef03886e62b626760763d95b15504b982aeb6582f03e412e99.jpg)  
Figure 12. Efficiency vs. output power  $(V_{CC} = 25\mathrm{V},\mathrm{load} = 6\Omega)$

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/cb09444520b5a458be9f46be0710b79c17a41ffb1ffc57769087eec7a9755538.jpg)  
Figure 13. Efficiency vs. output power  $(V_{CC} = 25\mathrm{V},\mathrm{load} = 8\Omega)$

# 4.1 Mono parallel BTL characteristics

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/ee07158b93587f0b48aa128dcce1ab51e1f85eab901530eb3d08a15b8c82613d.jpg)  
Figure 14. THD+N vs. output power (VCC = 25 V, load = 3 Ω)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/6d03e55d678ca90cc2b52164f217892a51ee38b9cdc5f55c0a9a265764f2f9de.jpg)  
Figure 15. Output power vs.  $V_{CC}$  (load = 3 Ω)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/f8eea654c61795b16c9b0662ad0f539e39ae5ab7b5b42d85181fbbdb80298e82.jpg)  
Figure 16. Efficiency vs. output power  $(V_{CC} = 26\mathrm{V},\mathrm{load} = 3\Omega)$

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/c9715bbacbc7faa964a3c2cf446fac8fb62185c56baf62373296096448445876.jpg)  
Figure 17. Efficiency vs. output power  $(V_{CC} = 18\mathrm{~V}, \text{load} = 3\Omega)$

# 5 Serial audio interface

The STA350Bx audio serial input interface has been designed to interface with standard digital audio components and to accept a number of serial data formats. The STA350Bx always acts as the slave when receiving audio input from standard digital audio components. Serial data for two channels is provided using three inputs: left/right clock LRCKI, serial clock BICKI, and serial data SD12.

The SAI bit and the SAIFB bit are used to specify the serial data format. The default serial data format is I²S, MSB-first.

# 5.0.1 Timings

In the STA350Bx the BICKI and LRCKI pins are configured as inputs and they must be supplied by the external peripheral.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/bcdfcd9b17680541ce1c74f11173acf062db86af747f213b423e4ea9a98547de.jpg)  
Figure 18. Timing diagram for SAI interface

Table 7. Timing parameters for slave mode  

<table><tr><td>Symbol</td><td>Parameter</td><td>Min.</td><td>Typ.</td><td>Max.</td><td>Unit</td></tr><tr><td>tBCy</td><td>BICK cycle time</td><td>80</td><td>-</td><td>-</td><td>ns</td></tr><tr><td>tBCH</td><td>BICK pulse width high</td><td>40</td><td>-</td><td>-</td><td>ns</td></tr><tr><td>tBCL</td><td>BICK pulse width low</td><td>40</td><td>-</td><td>-</td><td>ns</td></tr><tr><td>tLRSU</td><td>LRCKI setup time to BICKI strobing edge</td><td>40</td><td>-</td><td>-</td><td>ns</td></tr><tr><td>tLRH</td><td>LRCKI hold time to BICKI strobing edge</td><td>40</td><td>-</td><td>-</td><td>ns</td></tr><tr><td>tLRJT</td><td>LRCKI jitter tolerance</td><td></td><td></td><td>40</td><td>ns</td></tr></table>

# 5.0.2 Delay serial clock enable

To tolerate anomalies in some I²S master devices, a PLL clock cycle delay can be added to the BICKI signal before the SAI interface.

# 5.0.3 Channel input mapping

Each channel received via I²S can be mapped to any internal processing channel via the channel input mapping registers. This allows for flexibility in processing. The default settings of these registers map each I²S input channel to its corresponding processing channel.

# 6 Processing data paths

Figure 19 and 20 illustrate the data processing paths inside the STA350Bx.

The whole processing chain is composed of two consecutive sections. In the first one dual-channel processing is implemented, as described below, and then each channel is fed into the post-mixing block by generating either a third channel (typically used in 2.1 output configuration and with crossover filters enabled) or having the channels processed by the dual-band DRC block (2.0 output configuration with crossover filters used to define the cutoff frequency of the two bands).

The first section begins with a 2x oversampling FIR filter allowing for  $2^{*}\mathrm{Fs}$  audio processing. Then a selectable high-pass filter removes the DC level (enabled if HFB=0).

The channel 1 and 2 processing chain can include up to 8 filters, depending on the selected configuration (bits BQL, BQ5, BQ6, BQ7 and XO[3:0]).

By default 4 independent filters per channel are enabled, plus the pre-configured DeEmphasis, Bass and Treble controls (BQL=0, BQ5=0, BQ6=0, BQ7=0).

If the coefficient sets are linked (BQL=1) it's then possible to use De-Emphasis, Bass and Treble filter in a user-defined configuration (provided the relevant BQx bits are set). In other words both channels use the same processing coefficients and can have up to 7 filters each. Note that if BQL=0 the BQx bits are ignored and the  $5^{\text{th}}$ ,  $6^{\text{th}}$  and  $7^{\text{th}}$  filters are configured as, respectively, De-Emphasis, Bass and Treble controls.

Moreover the common  $8^{\text{th}}$  filter, from the subsequent processing section, can be available on both channels (provided the pre-defined crossover frequencies are not used, XO[3:0]=0, and the dual-band DRC is not used).

In the second section mixing and crossover filters are available. If  $B^{2}DRC$  is not enabled (Figure 20), they are fully user-programmable and allow generating a third channel (2.1 outputs). Alternatively, in  $B^{2}DRC$  mode, those blocks are used to split the sub-band and define the cutoff frequencies of the two bands. A prescaler and a final postScaler allow full control over the signal dynamic respectively before and after the filtering stages. A mixer function is also available.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/572dcec9b95c596e899cb362fbca3a93d41b102b5decf1bcc62cdbe7edef08e6.jpg)  
Figure 19. Left and right processing - part 1

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/260ae50fd07b6b60bc7506c0ae4184cc1ed421fdabf8e27f5b995c463e374602.jpg)  
Figure 20. Processing - part 2

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/85fe832f3d75cbad3838f6af2c56628a4afe6456f7d24043bc3ce2e72e4ade61.jpg)  
Dual-band DRC disabled

AM045182v1

# 7 I²C bus specification

The STA350Bx supports the  $\mathrm{I}^2\mathrm{C}$  protocol via the input ports SCL and SDA_IN (master to slave) and the output port SDA_OUT (slave to master). This protocol defines any device that sends data to the bus as a transmitter and any device that reads the data as a receiver. The device that controls the data transfer is known as the master and the other as the slave. The master always starts the transfer and provides data to the serial clock for synchronization. The STA350Bx is always a slave device in all of its communications. It supports up to 400 kb/s rate (fast-mode bit rate). The STA350Bx  $\mathrm{I}^2\mathrm{C}$  is a slave-only interface. The  $\mathrm{I}^2\mathrm{C}$  interface works properly only in the case that the master clock generated by the PLL has a frequency 10 times higher compared to the frequency of the applied SCL signal.

# 7.1 Communication protocol

# 7.1.1 Data transition or change

Data changes on the SDA line must only occur when the SCL clock is low. An SDA transition while the clock is high is used to identify a START or STOP condition.

# 7.1.2 Start condition

START is identified by a high-to-low transition of the data bus SDA signal while the clock signal SCL is stable in the high state. A START condition must precede any command for data transfer.

# 7.1.3 Stop condition

STOP is identified by a low-to-high transition of the data bus SDA signal while the clock signal SCL is stable in the high state. A STOP condition terminates communication between the STA350Bx and the bus master.

# 7.1.4 Data input

During data input the STA350Bx samples the SDA signal on the rising edge of clock SCL. For correct device operation the SDA signal must be stable during the rising edge of the clock and the data can change only when the SCL line is low.

# 7.2 Device addressing

To start communication between the master and the STA350Bx, the master must initiate a start condition. Following this, the master sends 8 bits (MSB first) corresponding to the device select address and read or write mode to the SDA line.

The seven most significant bits are the device address identifiers, corresponding to the  $\mathrm{I}^2\mathrm{C}$  bus definition. In the STA350Bx the  $\mathrm{I}^2\mathrm{C}$  interface has two device addresses depending on the SA port configuration, 0x38 when  $\mathrm{SA} = 0$ , and 0x3A when  $\mathrm{SA} = 1$ .

The eighth bit (LSB) identifies the read or write operation RW, this bit is set to 1 in read mode and to 0 for write mode. After a START condition the STA350Bx identifies on the bus

the device address and if a match is found, it acknowledges the identification on the SDA bus during the  $9^{\text{th}}$  bit time. The byte following the device identification byte is the internal space address.

# 7.3 Write operation

Following the START condition the master sends a device select code with the RW bit set to 0. The STA350Bx acknowledges this and then writes the byte of the internal address. After receiving the internal byte address the STA350Bx again responds with an acknowledgment.

# 7.3.1 Byte write

In the byte write mode the master sends one data byte, which is acknowledged by the STA350Bx. The master then terminates the transfer by generating a STOP condition.

# 7.3.2 Multi-byte write

The multi-byte write modes can start from any internal address. The master generating a STOP condition terminates the transfer.

# 7.4 Read operation

# 7.4.1 Current address byte read

Following the START condition the master sends a device select code with the RW bit set to 1. The STA350Bx acknowledges this and then responds by sending one byte of data. The master then terminates the transfer by generating a STOP condition.

# 7.4.2 Current address multi-byte read

The multi-byte read modes can start from any internal address. Sequential data bytes are read from sequential addresses within the STA350Bx. The master acknowledges each data byte read and then generates a STOP condition, terminating the transfer.

# 7.4.3 Random address byte read

Following the START condition the master sends a device select code with the RW bit set to 0. The STA350Bx acknowledges this and then the master writes the internal address byte. After receiving the internal byte address, the STA350Bx again responds with an acknowledgement. The master then initiates another START condition and sends the device select code with the RW bit set to 1. The STA350Bx acknowledges this and then responds by sending one byte of data. The master then terminates the transfer by generating a STOP condition.

# 7.4.4 Random address multi-byte read

The multi-byte read modes can start from any internal address. Sequential data bytes are read from sequential addresses within the STA350Bx. The master acknowledges each data byte read and then generates a STOP condition, terminating the transfer.

# 7.4.5 Write mode sequence

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/5abaec8f8f08fcac3bece23d2057d7f9ba89515d21decba77a55a39870b66778.jpg)  
Figure 21. Write mode sequence

# 7.4.6 Read mode sequence

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/51463d2bb5f5f5b000640f4a3ec068ea7c9122fa5bee42c66054d5d493744132.jpg)  
Figure 22. Read mode sequence

# 8 Register description

Table 8. Register summary  

<table><tr><td>Addr</td><td>Name</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>0x00</td><td>CONFA</td><td>FDRB</td><td>TWAB</td><td>TWRB</td><td>IR1</td><td>IR0</td><td>MCS2</td><td>MCS1</td><td>MCS0</td></tr><tr><td>0x01</td><td>CONFB</td><td>C2IM</td><td>C1IM</td><td>DSCKE</td><td>SAIFB</td><td>SAI3</td><td>SAI2</td><td>SAI1</td><td>SAI0</td></tr><tr><td>0x02</td><td>CONFC</td><td>OCRB</td><td></td><td>CSZ3</td><td>CSZ2</td><td>CSZ1</td><td>CSZ0</td><td>OM1</td><td>OM0</td></tr><tr><td>0x03</td><td>CONFD</td><td>SME</td><td>ZDE</td><td>DRC</td><td>BQL</td><td>PSL</td><td>DSPB</td><td>DEMP</td><td>HPB</td></tr><tr><td>0x04</td><td>CONFE</td><td>SVE</td><td>ZCE</td><td>DCCV</td><td>PWMS</td><td>AME</td><td>NSBW</td><td>MPC</td><td>MPCV</td></tr><tr><td>0x05</td><td>CONFF</td><td>EAPD</td><td>PWDN</td><td>ECLE</td><td>LDTE</td><td>BCLE</td><td>IDE</td><td>OCFG1</td><td>OCFG0</td></tr><tr><td>0x06</td><td>MUTE/LOC</td><td>LOC1</td><td>LOC0</td><td>Reserved</td><td>Reserved</td><td>C3M</td><td>C2M</td><td>C1M</td><td>MMUTE</td></tr><tr><td>0x07</td><td>MVOL</td><td>MV7</td><td>MV6</td><td>MV5</td><td>MV4</td><td>MV3</td><td>MV2</td><td>MV1</td><td>MV0</td></tr><tr><td>0x08</td><td>C1VOL</td><td>C1V7</td><td>C1V6</td><td>C1V5</td><td>C1V4</td><td>C1V3</td><td>C1V2</td><td>C1V1</td><td>C1V0</td></tr><tr><td>0x09</td><td>C2VOL</td><td>C2V7</td><td>C2V6</td><td>C2V5</td><td>C2V4</td><td>C2V3</td><td>C2V2</td><td>C2V1</td><td>C2V0</td></tr><tr><td>0x0A</td><td>C3VOL</td><td>C3V7</td><td>C3V6</td><td>C3V5</td><td>C3V4</td><td>C3V3</td><td>C3V2</td><td>C3V1</td><td>C3V0</td></tr><tr><td>0x0B</td><td>AUTO1</td><td>Reserved</td><td>Reserved</td><td>AMGC1</td><td>AMGC0</td><td>Reserved</td><td>Reserved</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0x0C</td><td>AUTO2</td><td>XO3</td><td>XO2</td><td>XO1</td><td>XO0</td><td>AMAM2</td><td>AMAM1</td><td>AMAM0</td><td>AMAME</td></tr><tr><td>0x0D</td><td>AUTO3</td><td colspan="8">Reserved</td></tr><tr><td>0x0E</td><td>C1CFG</td><td>C1OM1</td><td>C1OM0</td><td>C1LS1</td><td>C1LS0</td><td>C1BO</td><td>C1VBP</td><td>C1EQBP</td><td>C1TCB</td></tr><tr><td>0x0F</td><td>C2CFG</td><td>C2OM1</td><td>C2OM0</td><td>C2LS1</td><td>C2LS0</td><td>C2BO</td><td>C2VBP</td><td>C2EQBP</td><td>C2TCB</td></tr><tr><td>0x10</td><td>C3CFG</td><td>C3OM1</td><td>C3OM0</td><td>C3LS1</td><td>C3LS0</td><td>C3BO</td><td>C3VBP</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0x11</td><td>TONE</td><td>TTC3</td><td>TTC2</td><td>TTC1</td><td>TTC0</td><td>BTC3</td><td>BTC2</td><td>BTC1</td><td>BTC0</td></tr><tr><td>0x12</td><td>L1AR</td><td>L1A3</td><td>L1A2</td><td>L1A1</td><td>L1A0</td><td>L1R3</td><td>L1R2</td><td>L1R1</td><td>L1R0</td></tr><tr><td>0x13</td><td>L1ATRT</td><td>L1AT3</td><td>L1AT2</td><td>L1AT1</td><td>L1AT0</td><td>L1RT3</td><td>L1RT2</td><td>L1RT1</td><td>L1RT0</td></tr><tr><td>0x14</td><td>L2AR</td><td>L2A3</td><td>L2A2</td><td>L2A1</td><td>L2A0</td><td>L2R3</td><td>L2R2</td><td>L2R1</td><td>L2R0</td></tr><tr><td>0x15</td><td>L2ATRT</td><td>L2AT3</td><td>L2AT2</td><td>L2AT1</td><td>L2AT0</td><td>L2RT3</td><td>L2RT2</td><td>L2RT1</td><td>L2RT0</td></tr><tr><td>0x16</td><td>CFADDR</td><td>Reserved</td><td>Reserved</td><td>CFA5</td><td>CFA4</td><td>CFA3</td><td>CFA2</td><td>CFA1</td><td>CFA0</td></tr><tr><td>0x17</td><td>B1CF1</td><td>C1B23</td><td>C1B22</td><td>C1B21</td><td>C1B20</td><td>C1B19</td><td>C1B18</td><td>C1B17</td><td>C1B16</td></tr><tr><td>0x18</td><td>B1CF2</td><td>C1B15</td><td>C1B14</td><td>C1B13</td><td>C1B12</td><td>C1B11</td><td>C1B10</td><td>C1B9</td><td>C1B8</td></tr><tr><td>0x19</td><td>B1CF3</td><td>C1B7</td><td>C1B6</td><td>C1B5</td><td>C1B4</td><td>C1B3</td><td>C1B2</td><td>C1B1</td><td>C1B0</td></tr><tr><td>0x1A</td><td>B2CF1</td><td>C2B23</td><td>C2B22</td><td>C2B21</td><td>C2B20</td><td>C2B19</td><td>C2B18</td><td>C2B17</td><td>C2B16</td></tr><tr><td>0x1B</td><td>B2CF2</td><td>C2B15</td><td>C2B14</td><td>C2B13</td><td>C2B12</td><td>C2B11</td><td>C2B10</td><td>C2B9</td><td>C2B8</td></tr><tr><td>0x1C</td><td>B2CF3</td><td>C2B7</td><td>C2B6</td><td>C2B5</td><td>C2B4</td><td>C2B3</td><td>C2B2</td><td>C2B1</td><td>C2B0</td></tr><tr><td>0x1D</td><td>A1CF1</td><td>C3B23</td><td>C3B22</td><td>C3B21</td><td>C3B20</td><td>C3B19</td><td>C3B18</td><td>C3B17</td><td>C3B16</td></tr><tr><td>0x1E</td><td>A1CF2</td><td>C3B15</td><td>C3B14</td><td>C3B13</td><td>C3B12</td><td>C3B11</td><td>C3B10</td><td>C3B9</td><td>C3B8</td></tr><tr><td>0x1F</td><td>A1CF3</td><td>C3B7</td><td>C3B6</td><td>C3B5</td><td>C3B4</td><td>C3B3</td><td>C3B2</td><td>C3B1</td><td>C3B0</td></tr><tr><td>0x20</td><td>A2CF1</td><td>C4B23</td><td>C4B22</td><td>C4B21</td><td>C4B20</td><td>C4B19</td><td>C4B18</td><td>C4B17</td><td>C4B16</td></tr><tr><td>0x21</td><td>A2CF2</td><td>C4B15</td><td>C4B14</td><td>C4B13</td><td>C4B12</td><td>C4B11</td><td>C4B10</td><td>C4B9</td><td>C4B8</td></tr></table>

Table 8. Register summary (continued)  

<table><tr><td>Addr</td><td>Name</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>0x22</td><td>A2CF3</td><td>C4B7</td><td>C4B6</td><td>C4B5</td><td>C4B4</td><td>C4B3</td><td>C4B2</td><td>C4B1</td><td>C4B0</td></tr><tr><td>0x23</td><td>B0CF1</td><td>C5B23</td><td>C5B22</td><td>C5B21</td><td>C5B20</td><td>C5B19</td><td>C5B18</td><td>C5B17</td><td>C5B16</td></tr><tr><td>0x24</td><td>B0CF2</td><td>C5B15</td><td>C5B14</td><td>C5B13</td><td>C5B12</td><td>C5B11</td><td>C5B10</td><td>C5B9</td><td>C5B8</td></tr><tr><td>0x25</td><td>B0CF3</td><td>C5B7</td><td>C5B6</td><td>C5B5</td><td>C5B4</td><td>C5B3</td><td>C5B2</td><td>C5B1</td><td>C5B0</td></tr><tr><td>0x26</td><td>CFUD</td><td colspan="4">Reserved</td><td>RA</td><td>R1</td><td>WA</td><td>W1</td></tr><tr><td>0x27</td><td>MPCC1</td><td>MPCC15</td><td>MPCC14</td><td>MPCC13</td><td>MPCC12</td><td>MPCC11</td><td>MPCC10</td><td>MPCC9</td><td>MPCC8</td></tr><tr><td>0x28</td><td>MPCC2</td><td>MPCC7</td><td>MPCC6</td><td>MPCC5</td><td>MPCC4</td><td>MPCC3</td><td>MPCC2</td><td>MPCC1</td><td>MPCC0</td></tr><tr><td>0x29</td><td>DCC1</td><td>DCC15</td><td>DCC14</td><td>DCC13</td><td>DCC12</td><td>DCC11</td><td>DCC10</td><td>DCC9</td><td>DCC8</td></tr><tr><td>0x2A</td><td>DCC2</td><td>DCC7</td><td>DCC6</td><td>DCC5</td><td>DCC4</td><td>DCC3</td><td>DCC2</td><td>DCC1</td><td>DCC0</td></tr><tr><td>0x2B</td><td>FDRC1</td><td>FDRC15</td><td>FDRC14</td><td>FDRC13</td><td>FDRC12</td><td>FDRC11</td><td>FDRC10</td><td>FDRC9</td><td>FDRC8</td></tr><tr><td>0x2C</td><td>FDRC2</td><td>FDRC7</td><td>FDRC6</td><td>FDRC5</td><td>FDRC4</td><td>FDRC3</td><td>FDRC2</td><td>FDRC1</td><td>FDRC0</td></tr><tr><td>0x2D</td><td>STATUS</td><td>PLLUL</td><td>FAULT</td><td>UVFAULT</td><td>OVFAULT</td><td>OCFAULT</td><td>OCWARN</td><td>TFAULT</td><td>TWARN</td></tr><tr><td>0x2E</td><td>Reserved</td><td colspan="2">Reserved</td><td>RO1BACT</td><td>R5BACT</td><td>R4BACT</td><td>R3BACT</td><td>R2BACT</td><td>R1BACT</td></tr><tr><td>0x2F</td><td>Reserved</td><td colspan="2">Reserved</td><td>R01BEND</td><td>R5BEND</td><td>R4BEND</td><td>R3BEND</td><td>R2BEND</td><td>R1BEND</td></tr><tr><td>0x30</td><td>Reserved</td><td colspan="3">Reserved</td><td>R5BBAD</td><td>R4BBAD</td><td>R3BBAD</td><td>R2BBAD</td><td>R1BBAD</td></tr><tr><td>0x31</td><td>EQCFG</td><td>XOB</td><td>Reserved</td><td>Reserved</td><td>AMGC3</td><td>AMGC2</td><td>Reserved</td><td>SEL1</td><td>SEL0</td></tr><tr><td>0x32</td><td>EATH1</td><td>EATHEN1</td><td>EATH1[6]</td><td>EATH1[5]</td><td>EATH1[4]</td><td>EATH1[3]</td><td>EATH1[2]</td><td>EATH1[1]</td><td>EATH1[0]</td></tr><tr><td>0x33</td><td>ERTH1</td><td>ERTHEN1</td><td>ERTH1[6]</td><td>ERTH1[5]</td><td>ERTH1[4]</td><td>ERTH1[3]</td><td>ERTH1[2]</td><td>ERTH1[1]</td><td>ERTH1[0]</td></tr><tr><td>0x34</td><td>EATH2</td><td>EATHEN2</td><td>EATH2[6]</td><td>EATH2[5]</td><td>EATH2[4]</td><td>EATH2[3]</td><td>EATH2[2]</td><td>EATH2[1]</td><td>EATH2[0]</td></tr><tr><td>0x35</td><td>ERTH2</td><td>ERTHEN2</td><td>ERTH2[6]</td><td>ERTH2[5]</td><td>ERTH2[4]</td><td>ERTH2[3]</td><td>ERTH2[2]</td><td>ERTH2[1]</td><td>ERTH2[0]</td></tr><tr><td>0x36</td><td>CONFX</td><td>MDRC[1]</td><td>MDRC[0]</td><td>PS48DB</td><td>XAR1</td><td>XAR2</td><td>BQ5</td><td>BQ6</td><td>BQ7</td></tr><tr><td>0x37</td><td>SVCA</td><td>Reserved</td><td>Reserved</td><td>SVUPE</td><td>SVUP[4]</td><td>SVUP[3]</td><td>SVUP[2]</td><td>SVUP[1]</td><td>SVUP[0]</td></tr><tr><td>0x38</td><td>SVCB</td><td>Reserved</td><td>Reserved</td><td>SVDWE</td><td>SVDW[4]</td><td>SVDW[3]</td><td>SVDW[2]</td><td>SVDW[1]</td><td>SVDW[0]</td></tr><tr><td>0x39</td><td>RMS0A</td><td>R_C0[23]</td><td>R_C0[22]</td><td>R_C0[21]</td><td>R_C0[20]</td><td>R_C0[19]</td><td>R_C0[18]</td><td>R_C0[17]</td><td>R_C0[16]</td></tr><tr><td>0x3A</td><td>RMS0B</td><td>R_C0[15]</td><td>R_C0[14]</td><td>R_C0[13]</td><td>R_C0[12]</td><td>R_C0[11]</td><td>R_C0[10]</td><td>R_C0[9]</td><td>R_C0[8]</td></tr><tr><td>0x3B</td><td>RMS0C</td><td>R_C0[7]</td><td>R_C0[6]</td><td>R_C0[5]</td><td>R_C0[4]</td><td>R_C0[3]</td><td>R_C0[2]</td><td>R_C0[1]</td><td>R_C0[0]</td></tr><tr><td>0x3C</td><td>RMS1A</td><td>R_C1[23]</td><td>R_C1[22]</td><td>R_C1[21]</td><td>R_C1[20]</td><td>R_C1[19]</td><td>R_C1[18]</td><td>R_C1[17]</td><td>R_C1[16]</td></tr><tr><td>0x3D</td><td>RMS1B</td><td>R_C1[15]</td><td>R_C1[14]</td><td>R_C1[13]</td><td>R_C1[12]</td><td>R_C1[11]</td><td>R_C1[10]</td><td>R_C1[9]</td><td>R_C1[8]</td></tr><tr><td>0x3E</td><td>RMS1C</td><td>R_C1[7]</td><td>R_C1[6]</td><td>R_C1[5]</td><td>R_C1[4]</td><td>R_C1[3]</td><td>R_C1[2]</td><td>R_C1[1]</td><td>R_C1[0]</td></tr><tr><td>0x3F</td><td>EVOLRES</td><td>VRESEN</td><td>VRESTG</td><td>C3VR[1]</td><td>C3VR[0]</td><td>C2VR[1]</td><td>C2VR[0]</td><td>C1VR[1]</td><td>C1VR[0]</td></tr><tr><td>0x40</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x41</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x42</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x43</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x44</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x45</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x46</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

Table 8. Register summary (continued)  

<table><tr><td>Addr</td><td>Name</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>0x47</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x48</td><td>NSHAPE</td><td>NSHXEN</td><td>NSHB7EN</td><td>NSHB6EN</td><td>NSHB5EN</td><td>NSHB4EN</td><td>NSHB3EN</td><td>NSHB2EN</td><td>NSHB1EN</td></tr><tr><td>0x49</td><td>CXT[B4B1]</td><td>CXTB4[1]</td><td>CXTB4[0]</td><td>CXTB3[1]</td><td>CXTB3[0]</td><td>CXTB2[1]</td><td>CXTB2[0]</td><td>CXTB1[1]</td><td>CXTB1[0]</td></tr><tr><td>0x4A</td><td>CXT[B7B5]</td><td>Reserved</td><td>Reserved</td><td>CXTB7[1]</td><td>CXTB7[0]</td><td>CXTB6[1]</td><td>CXTB6[0]</td><td>CXTB5[1]</td><td>CXTB5[0]</td></tr><tr><td>0x4B</td><td>MISC1</td><td>RPDNEN</td><td>NSHHPEN</td><td>BRIDGOFF</td><td>Reserved</td><td>Reserved</td><td>CPWMEN</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0x4C</td><td>MISC2</td><td>Reserved</td><td>Reserved</td><td>Reserved</td><td>PNDLSL[2]</td><td>PNDLSL[1]</td><td>PNDLSL[0]</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0x4D</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x4E</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x4F</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x50</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x51</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x52</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x53</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x54</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x55</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0x56</td><td>Reserved</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

# 8.1 Configuration register A (addr 0x00)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>FDRB</td><td>TWAB</td><td>TWRB</td><td>IR1</td><td>IR0</td><td>MCS2</td><td>MCS1</td><td>MCS0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td></tr></table>

# 8.1.1 Master clock select

Table 9. Master clock select  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>1</td><td>MCS0</td><td rowspan="3">Selects the ratio between the input I²S sample frequency and the input clock.</td></tr><tr><td>1</td><td>R/W</td><td>1</td><td>MCS1</td></tr><tr><td>2</td><td>R/W</td><td>0</td><td>MCS2</td></tr></table>

The STA350Bx supports sample rates of 32 kHz, 44.1 kHz, 48 kHz, 88.2 kHz, 96 kHz, 176.4 kHz, and 192 kHz. Therefore the internal clock is:

32.768 MHz for 32 kHz  
45.1584 MHz for 44.1 kHz, 88.2 kHz, and 176.4 kHz  
49.152 MHz for 48 kHz, 96 kHz, and 192 kHz

The external clock frequency provided to the XTI pin must be a multiple of the input sample frequency  $(f_{s})$ .

The relationship between the input clock and the input sample rate is determined by both the MCSx and the IR (input rate) register bits. The MCSx bits determine the PLL factor generating the internal clock and the IR bit determines the oversampling ratio used internally.

Table 10. Input sampling rates  

<table><tr><td>Input sample rate fs (kHz)</td><td>IR</td><td colspan="6">MCS[2:0]</td></tr><tr><td></td><td></td><td>101</td><td>100</td><td>011</td><td>010</td><td>001</td><td>000</td></tr><tr><td>32, 44.1, 48</td><td>00</td><td>576 * fs</td><td>128 * fs</td><td>256 * fs</td><td>384 * fs</td><td>512 * fs</td><td>768 * fs</td></tr><tr><td>88.2, 96</td><td>01</td><td>NA</td><td>64 * fs</td><td>128 * fs</td><td>192 * fs</td><td>256 * fs</td><td>384 * fs</td></tr><tr><td>176.4, 192</td><td>1X</td><td>NA</td><td>32 * fs</td><td>64 * fs</td><td>96 * fs</td><td>128 * fs</td><td>192 * fs</td></tr></table>

# 8.1.2 Interpolation ratio select

Table 11. Internal interpolation ratio  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>4:3</td><td>R/W</td><td>00</td><td>IR [1:0]</td><td>Selects internal interpolation ratio based on input I²S sample frequency</td></tr></table>

The STA350Bx has variable interpolation (oversampling) settings such that internal processing and FFX output rates remain consistent. The first processing block interpolates by either 2-times or 1-time (pass-through) or provides a 2-times downsample. The oversampling ratio of this interpolation is determined by the IR bits.

Table 12. IR bit settings as a function of input sample rate  

<table><tr><td>Input sample rate fs (kHz)</td><td>IR</td><td>1ststage interpolation ratio</td></tr><tr><td>32</td><td>00</td><td>2 times oversampling</td></tr><tr><td>44.1</td><td>00</td><td>2 times oversampling</td></tr><tr><td>48</td><td>00</td><td>2 times oversampling</td></tr><tr><td>88.2</td><td>01</td><td>Pass-through</td></tr><tr><td>96</td><td>01</td><td>Pass-through</td></tr><tr><td>176.4</td><td>10</td><td>2 times downsampling</td></tr><tr><td>192</td><td>10</td><td>2 times downsampling</td></tr></table>

# 8.1.3 Thermal warning recovery bypass

Table 13. Thermal warning recovery bypass  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>5</td><td>R/W</td><td>1</td><td>TWRB</td><td>0: Thermal warning recovery enabled
1: Thermal warning recovery disabled</td></tr></table>

If the thermal warning adjustment is enabled (TWAB = 0), then the thermal warning recovery determines if the -3 dB output limit is removed when thermal warning is negative.

If TWRB = 0 and TWAB = 0, then when a thermal warning disappears the -3 dB output limit is removed and the gain is added back to the system. If TWRB = 1 and TWAB = 0, then when a thermal warning disappears the -3 dB output limit remains until TWRB is changed to zero or the device is reset.

# 8.1.4 Thermal warning adjustment bypass

Table 14. Thermal warning adjustment bypass  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>6</td><td>R/W</td><td>1</td><td>TWAB</td><td>0: Thermal warning adjustment enabled
1: Thermal warning adjustment disabled</td></tr></table>

The on-chip STA350Bx power output block provides feedback to the digital controller using inputs to the power control block. Input TWARN is used to indicate a thermal warning condition. When TWARN is asserted (set to 0) for a period of time greater than  $400\mathrm{ms}$ , the power control block forces a -3 dB output limit (determined by TWOOCL in the coefficient RAM) to the modulation limit in an attempt to eliminate the thermal warning condition. Once the thermal warning output limit adjustment is applied, it remains in this state until reset, unless FDRB = 0.

# 8.1.5 Fault detect recovery bypass

Table 15. Fault detect recovery bypass  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R/W</td><td>0</td><td>FDRB</td><td>0: fault detect recovery enabled
1: fault detect recovery disabled</td></tr></table>

The on-chip STA350Bx power output block provides feedback to the digital controller using inputs to the power control block. The FAULT input is used to indicate a fault condition (either over-current or thermal). When FAULT is asserted (set to 0), the power control block attempts a recovery from the fault by asserting the tri-state output (setting it to 0 which directs the power output block to begin recovery), holds it at 0 for period of time in the range of 0.1 ms to 1 second as defined by the fault-detect recovery constant register (FDRC registers 0x29-0x2A), then toggles it back to 1. This sequence is repeated as long as the fault indication exists. This feature is enabled by default but can be bypassed by setting the FDRB control bit to 1.

# 8.2 Configuration register B (addr 0x01)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C2IM</td><td>C1IM</td><td>DSCKE</td><td>SAIFB</td><td>SAI3</td><td>SAI2</td><td>SAI1</td><td>SAI0</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.2.1 Serial audio input interface format

Table 16. Serial audio input interface  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>0</td><td>SAI0</td><td rowspan="4">Determines the interface format of the input serial digital audio interface.</td></tr><tr><td>1</td><td>R/W</td><td>0</td><td>SAI1</td></tr><tr><td>2</td><td>R/W</td><td>0</td><td>SAI2</td></tr><tr><td>3</td><td>R/W</td><td>0</td><td>SAI3</td></tr></table>

# 8.2.2 Serial data interface

The STA350Bx audio serial input was designed to interface with standard digital audio components and to accept a number of serial data formats. The STA350Bx always acts as the slave when receiving audio input from standard digital audio components. Serial data for two channels is provided using three inputs: left/right clock LRCKI, serial clock BICKI, and serial data 1 and 2 SDI12.

The SAI bits (D3 to D0) and the SAIFB bit (D4) are used to specify the serial data format. The default serial data format is I²S, MSB-first. Available formats are shown in the tables that follow.

# 8.2.3 Serial data first bit

Table 17. Serial data first bit  

<table><tr><td>SAIFB</td><td>Format</td></tr><tr><td>0</td><td>MSB-first</td></tr><tr><td>1</td><td>LSB-first</td></tr></table>

Table 18. Support serial audio input formats for MSB-first (SAIFB = 0)  

<table><tr><td>BICKI</td><td>SAI [3:0]</td><td>SAIFB</td><td>Interface format</td></tr><tr><td rowspan="2">32 * fs</td><td>0000</td><td>0</td><td>I²S 15-bit data</td></tr><tr><td>0001</td><td>0</td><td>Left/right-justified 16-bit data</td></tr><tr><td rowspan="6">48 * fs</td><td>0000</td><td>0</td><td>I²S 16 to 23-bit data</td></tr><tr><td>0001</td><td>0</td><td>Left-justified 16 to 24-bit data</td></tr><tr><td>0010</td><td>0</td><td>Right-justified 24-bit data</td></tr><tr><td>0110</td><td>0</td><td>Right-justified 20-bit data</td></tr><tr><td>1010</td><td>0</td><td>Right-justified 18-bit data</td></tr><tr><td>1110</td><td>0</td><td>Right-justified 16-bit data</td></tr><tr><td rowspan="6">64 * fs</td><td>0000</td><td>0</td><td>I²S 16 to 24-bit data</td></tr><tr><td>0001</td><td>0</td><td>Left-justified 16 to 24-bit data</td></tr><tr><td>0010</td><td>0</td><td>Right-justified 24-bit data</td></tr><tr><td>0110</td><td>0</td><td>Right-justified 20-bit data</td></tr><tr><td>1010</td><td>0</td><td>Right-justified 18-bit data</td></tr><tr><td>1110</td><td>0</td><td>Right- justified 16-bit data</td></tr></table>

Table 19. Supported serial audio input formats for LSB-first (SAIFB = 1)  

<table><tr><td>BICKI</td><td>SAI [3:0]</td><td>SAIFB</td><td>Interface format</td></tr><tr><td rowspan="2">32 * fs</td><td>1100</td><td>1</td><td>I²S 15-bit data</td></tr><tr><td>1110</td><td>1</td><td>Left/right-justified 16-bit data</td></tr><tr><td rowspan="12">48 * fs</td><td>0100</td><td>1</td><td>I²S 23-bit data</td></tr><tr><td>0100</td><td>1</td><td>I²S 20-bit data</td></tr><tr><td>1000</td><td>1</td><td>I²S 18-bit data</td></tr><tr><td>1100</td><td>1</td><td>LSB first I²S 16-bit data</td></tr><tr><td>0001</td><td>1</td><td>Left-justified 24-bit data</td></tr><tr><td>0101</td><td>1</td><td>Left-justified 20-bit data</td></tr><tr><td>1001</td><td>1</td><td>Left-justified 18-bit data</td></tr><tr><td>1101</td><td>1</td><td>Left-justified 16-bit data</td></tr><tr><td>0010</td><td>1</td><td>Right-justified 24-bit data</td></tr><tr><td>0110</td><td>1</td><td>Right-justified 20-bit data</td></tr><tr><td>1010</td><td>1</td><td>Right-justified 18-bit data</td></tr><tr><td>1110</td><td>1</td><td>Right-justified 16-bit data</td></tr><tr><td rowspan="12">64 * fs</td><td>0000</td><td>1</td><td>I²S 24-bit data</td></tr><tr><td>0100</td><td>1</td><td>I²S 20-bit data</td></tr><tr><td>1000</td><td>1</td><td>I²S 18-bit data</td></tr><tr><td>1100</td><td>1</td><td>LSB first I²S 16-bit data</td></tr><tr><td>0001</td><td>1</td><td>Left-justified 24-bit data</td></tr><tr><td>0101</td><td>1</td><td>Left-justified 2O-bit data</td></tr><tr><td>1001</td><td>1</td><td>Left-justified 18-bit data</td></tr><tr><td>1101</td><td>1</td><td>Left-justified 16-bit data</td></tr><tr><td>0010</td><td>1</td><td>Right-justified 24-bit data</td></tr><tr><td>0110</td><td>1</td><td>Right-justified 20-bit data</td></tr><tr><td>1010</td><td>1</td><td>Right-justified 1B-bit data</td></tr><tr><td>1110</td><td>1</td><td>Right-justified 16-bit data</td></tr></table>

To make the STA350Bx work properly, the serial audio interface LRCKI clock must be synchronous to the PLL output clock. It means that:

- the frequency of PLL clock / frequency of LRCKI = N ±4 cycles, where N depends on the settings in Table 12 on page 38  
- the PLL must be locked.

If these two conditions are not met, and the IDE bit (reg 0x05 bit 2) is set to 1, the STA350Bx will immediately mute the I²S PCM data out (provided to the processing block) and it freezes any active processing task.

To avoid any audio side effects (like pop noise), it is strongly recommended to soft-mute any audio streams flowing into the STA350Bx data path before the desynchronize event happens. At the same time any processing related to the  $\mathrm{I}^2\mathrm{C}$  configuration should be issued only after the serial audio interface and the internal PLL are synchronous again.

Note: Any mute or volume change causes some delay in the completion of the  $I^2C$  operation due to the soft-volume feature. The soft-volume phase change must be finished before any clock desynchronization.

# 8.2.4 Delay serial clock enable

Table 20. Delay serial clock enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>5</td><td>R/W</td><td>0</td><td>DSCKE</td><td>0: No serial clock delay
1: Serial clock delay by 1 core clock cycle to tolerate anomalies in some I²S master devices</td></tr></table>

# 8.2.5 Channel input mapping

Table 21. Channel input mapping  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>6</td><td>R/W</td><td>0</td><td>C1IM</td><td>0: Processing channel 1 receives Left I2S Input
1: Processing channel 1 receives Right I2S Input</td></tr><tr><td>7</td><td>R/W</td><td>1</td><td>C2IM</td><td>0: Processing channel 2 receives Left I2S Input
1: Processing channel 2 receives Right I2S Input</td></tr></table>

Each channel received via  $\mathsf{I}^2\mathsf{S}$  can be mapped to any internal processing channel via the Channel Input Mapping registers. This allows for flexibility in processing. The default settings of these registers map each  $\mathsf{I}^2\mathsf{S}$  input channel to its corresponding processing channel.

# 8.3 Configuration register C (addr 0x02)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>OCRB</td><td></td><td>CSZ3</td><td>CSZ2</td><td>CSZ1</td><td>CSZ0</td><td>OM1</td><td>OM0</td></tr><tr><td>1</td><td></td><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td></tr></table>

# 8.3.1 FFX power output mode

Table 22. FFX power output mode  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>1</td><td>OM0</td><td rowspan="2">Selects configuration of FFX output</td></tr><tr><td>1</td><td>R/W</td><td>1</td><td>OM1</td></tr></table>

The FFX power output mode selects how the FFX output timing is configured.

Different power devices use different output modes.

Table 23. Output modes  

<table><tr><td>OM[1,0]</td><td>Output stage mode</td></tr><tr><td>00</td><td>Drop compensation</td></tr><tr><td>01</td><td>Discrete output stage - tapered compensation</td></tr><tr><td>10</td><td>Full power mode</td></tr><tr><td>11</td><td>Variable drop compensation (CSZx bits)</td></tr></table>

# 8.3.2 FFX compensating pulse size register

Table 24. FFX compensating pulse size bits  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>2</td><td>R/W</td><td>1</td><td>CSZ0</td><td rowspan="4">When OM[1,0] = 11, this register determines the size of the FFX compensating pulse from 0 clock ticks to 15 clock ticks</td></tr><tr><td>3</td><td>R/W</td><td>1</td><td>CSZ1</td></tr><tr><td>4</td><td>R/W</td><td>1</td><td>CSZ2</td></tr><tr><td>5</td><td>R/W</td><td>0</td><td>CSZ3</td></tr></table>

Table 25. Compensating pulse size  

<table><tr><td>CSZ[3:0]</td><td>Compensating pulse size</td></tr><tr><td>0000</td><td>0 ns (0 tick) compensating pulse size</td></tr><tr><td>0001</td><td>20 ns (1 tick) clock period compensating pulse size</td></tr><tr><td>...</td><td>...</td></tr><tr><td>1111</td><td>300 ns (15 tick) clock period compensating pulse size</td></tr></table>

# 8.3.3 Overcurrent warning detect adjustment bypass

Table 26. Overcurrent warning bypass  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R/W</td><td>1</td><td>OCRB</td><td>0: Overcurrent warning adjustment enabled
1: Overcurrent warning adjustment disabled</td></tr></table>

The OCWARN input is used to indicate an overcurrent warning condition. When OCWARN is asserted (set to 0), the power control block forces an adjustment to the modulation limit (default is -3 dB) in an attempt to eliminate the overcurrent warning condition. Once the overcurrent warning volume adjustment is applied, it remains in this state until a reset occurs. The level of adjustment can be changed via the TWOOL (thermal warning/over current limit) setting which is address 0x37 of the user-defined coefficient RAM.

# 8.4 Configuration register D (addr 0x03)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>SME</td><td>ZDE</td><td>DRC</td><td>BQL</td><td>PSL</td><td>DSPB</td><td>DEMP</td><td>HPB</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.4.1 High-pass filter bypass

Table 27. High-pass filter bypass  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>0</td><td>HPB</td><td>Setting of one bypasses internal AC coupling digital high-pass filter</td></tr></table>

The STA350Bx features an internal digital high-pass filter for the purpose of AC coupling. The purpose of this filter is to prevent DC signals from passing through an FFX amplifier. DC signals can cause speaker damage. When HPB = 0, this filter is enabled.

# 8.4.2 De-emphasis

Table 28. De-emphasis  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>1</td><td>R/W</td><td>0</td><td>DEMP</td><td>0: No de-emphasis
1: Enable de-emphasis on all channels</td></tr></table>

# 8.4.3 DSP bypass

Table 29. DSP bypass  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>2</td><td>R/W</td><td>0</td><td>DSPB</td><td>0: Normal operation
1: Bypass of biquad and bass/treble functions</td></tr></table>

Setting the DSPB bit to 1 bypasses the EQ function of the STA350Bx.

# 8.4.4 Post-scale link

Table 30. Post-scale link  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>3</td><td>R/W</td><td>0</td><td>PSL</td><td>0: Each channel uses individual post-scale value
1: Each channel uses channel 1 post-scale value</td></tr></table>

Post-scale functionality can be used for power-supply error correction. For multi-channel applications running off the same power-supply, the post-scale values can be linked to the value of channel 1 for ease of use and to update the values faster.

# 8.4.5 Biquad coefficient link

Table 31. Biquad coefficient link  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>4</td><td>R/W</td><td>0</td><td>BQL</td><td>0: Each channel uses coefficient values
1: Each channel uses channel 1 coefficient values</td></tr></table>

For ease of use, all channels can use the biquad coefficients loaded into the channel-1 coefficient RAM space by setting the BQL bit to 1. Therefore, any EQ updates have to be performed only once.

# 8.4.6 Dynamic range compression/anti-clipping bit

Table 32. Dynamic range compression/anti-clipping bit  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>5</td><td>R/W</td><td>0</td><td>DRC</td><td>0: Limiters act in anti-clipping mode
1: Limiters act in dynamic range compression mode</td></tr></table>

Both limiters can be used in one of two ways, anti-clipping or dynamic range compression. When used in anti-clipping mode the limiter threshold values are constant and dependent on the limiter settings. In dynamic range compression mode the limiter threshold values vary with the volume settings allowing a nighttime listening mode that provides a reduction in the dynamic range regardless of the volume level.

# 8.4.7 Zero-detect mute enable

Table 33. Zero-detect mute enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>6</td><td>R/W</td><td>1</td><td>ZDE</td><td>Setting of 1 enables the automatic zero-detect mute</td></tr></table>

Setting the ZDE bit enables the zero-detect automatic mute. The zero-detect circuit looks at the data for each processing channel at the output of the crossover (bass management) filter. If any channel receives 2048 consecutive zero value samples (regardless of  $f_s$ ) then that individual channel is muted if this function is enabled.

# 8.4.8 Submix mode enable

Table 34. Sub-mix mode enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R/W</td><td>0</td><td>SME</td><td>0: Sub-mix into left/right disabled
1: Sub-mix into left/right enabled</td></tr></table>

# 8.5 Configuration register E (addr 0x04)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>SVE</td><td>ZCE</td><td>DCCV</td><td>PWMS</td><td>AME</td><td>NSBW</td><td>MPC</td><td>MPCV</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td></tr></table>

# 8.5.1 Max. power correction variable

Table 35. Max. power correction variable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>0</td><td>MPCV</td><td>0: Use standard MPC coefficient
1: Use MPCC bits for MPC coefficient</td></tr></table>

# 8.5.2 Max. power correction

Table 36. Max. power correction  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>1</td><td>R/W</td><td>1</td><td>MPC</td><td>Setting of 1 enables power bridge correction for THD reduction near maximum power output</td></tr></table>

Setting the MPC bit turns on special processing that corrects the STA350Bx power device at high power. This mode should lower the  $\mathrm{THD + N}$  of a full FFX system at maximum power output and slightly below. If enabled, MPC is operational in all output modes except tapered  $(\mathrm{OM}[1,0] = 01)$  and binary. When OCFG  $= 00$  , MPC does not effect channels 3 and 4, the line-out channels.

# 8.5.3 Noise-shaper bandwidth selection

Table 37. Noise-shaper bandwidth selection  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>2</td><td>R/W</td><td>0</td><td>NSBW</td><td>1: Third order NS
0: Fourth order NS</td></tr></table>

# 8.5.4 AM mode enable

Table 38. AM mode enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>3</td><td>R/W</td><td>0</td><td>AME</td><td>0: Normal FFX operation
1: AM reduction mode FFX operation</td></tr></table>

The STA350Bx features an FFX processing mode that minimizes the amount of noise generated in the frequency range of AM radio. This mode is intended to be used when FFX operates in a device with an AM tuner active. The SNR of the FFX processing is reduced to approximately 83 dB in this mode, which is still greater than the SNR of AM radio.

# 8.5.5 PWM speed mode

Table 39. PWM speed mode  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>4</td><td>R/W</td><td>0</td><td>PWMS</td><td>0: Normal speed (384 kHz) all channels
1: Odd speed (341.3 kHz) all channels</td></tr></table>

# 8.5.6 Distortion compensation variable enable

Table 40. Distortion compensation variable enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>5</td><td>R/W</td><td>0</td><td>DCCV</td><td>0: Use preset DC coefficient
1: Use DCC coefficient</td></tr></table>

# 8.5.7 Zero-crossing volume enable

Table 41. Zero-crossing volume enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>6</td><td>R/W</td><td>1</td><td>ZCE</td><td>1: Volume adjustments only occur at digital zero-crossings
0: Volume adjustments occur immediately</td></tr></table>

The ZCE bit enables zero-crossing volume adjustments. When volume is adjusted on digital zero-crossings, no clicks are audible.

# 8.5.8 Soft-volume update enable

Table 42. Soft-volume update enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R/W</td><td>1</td><td>SVE</td><td>1: Volume adjustments ramp according to SVR settings
0: Volume adjustments occur immediately</td></tr></table>

# 8.6 Configuration register F (addr 0x05)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>EAPD</td><td>PWDN</td><td>ECLE</td><td>LDTE</td><td>BCLE</td><td>IDE</td><td>OCFG1</td><td>OCFG0</td></tr><tr><td>0</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td></tr></table>

# 8.6.1 Output configuration

Table 43. Output configuration  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>0</td><td>OCFG0</td><td rowspan="2">Selects the output configuration</td></tr><tr><td>1</td><td>R/W</td><td>0</td><td>OCFG1</td></tr></table>

Table 44. Output configuration engine selection  

<table><tr><td>OCFG[1:0]</td><td>Output configuration</td><td>Config pin</td></tr><tr><td>00</td><td>2-channel (full-bridge) power, 2-channel data-out: 
1A/1B → 1A/1B 
2A/2B → 2A/2B 
LineOut1 → 3A/3B 
LineOut2 → 4A/4B 
Line out configuration determined by LOC register</td><td>0</td></tr><tr><td>01</td><td>2(half-bridge).1(full-bridge) on-board power: 
1A → 1A Binary 0° 
2A → 1B Binary 90° 
3A/3B → 2A/2B Binary 45° 
1A/B → 3A/B Binary 0° 
2A/B → 4A/B Binary 90°</td><td>0</td></tr><tr><td>10</td><td>2 Channel (full-bridge) power, 1 channel FFX: 
1A/1B → 1A/1B 
2A/2B → 2A/2B 
3A/3B → 3A/3B 
EAPDEXT and TWARNEXT Active</td><td>0</td></tr><tr><td>11</td><td>1 Channel mono-parallel: 
3A → 1A/1B w/ C3BO 45° 
3B → 2A/2B w/ C3BO 45° 
1A/1B → 3A/3B 
2A/2B → 4A/4B</td><td>1</td></tr></table>

Note:

To the left of the arrow, the processing channel is shown. When using channel output mapping, any of the three processing channel outputs can be used for any of the three inputs.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/2f2d26ba0fb95d05871e9b59f139b2d7aa70324aa7d6881f5595411a14c4c760.jpg)  
Figure 23. OCFG = 00 (default value)

AM045185v1

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/484162d5e9cc6972c0409f8fffeb197c3464f37dab0c2f1468a197cf730f3f02.jpg)  
Figure 24. OCFG = 01

AM045186v1

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/133250b59a9de0a154e907ebaf4b0b4abaaed43d4e42e218648e4595befedbba.jpg)  
Figure 25. OCFG = 10

AM045187v1

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/babd1cd28896e75bae64782346f195eb3108ff28ca546161ceca114deb0dc881.jpg)  
Figure 26. OCFG = 11

The STA350Bx can be configured to support different output configurations. For each PWM output channel a PWM slot is defined. A PWM slot is always 1 / (8 * fs) second length. The PWM slot defines the maximum extension for the PWM rising and falling edge, that is, the rising edge as well as the falling edge cannot range outside the PWM slot boundaries.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/75640c10ecc4117f02d74f72fee49c21a63a3e5f776a3c172da7b2f8ea1fd920.jpg)  
Figure 27. Output mapping scheme

For each configuration the PWM signals from the digital driver are mapped in different ways to the power stage.

# 2.0 channels, two full-bridges (OCFG = 00)

- FFX1A -> OUT1A  
- FFX1B -> OUT1B  
FFX2A->OUT2A  
FFX2B->OUT2B  
FFX3A->OUT3A  
FFX3B->OUT3B  
FFX4A->OUT4A  
FFX4B->OUT4B  
- FFX1A/1B configured as ternary  
- FFX2A/2B configured as ternary  
- FFX3A/3B configured as lineage ternary  
- FFX4A/4B configured as lineage ternary

On channel 3 line out (LOC bits = 00) the same data as channel 1 processing is sent. On channel 4 line out (LOC bits = 00) the same data as channel 2 processing is sent. In this configuration, neither volume control nor EQ has any effect on channels 3 and 4.

In this configuration the PWM slot phase is the following as shown in Figure 28.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/2548e7f6df32a8a938bb9a5d7cb83aedad68d8827a52421bdb01b0400461b7d6.jpg)  
Figure 28. 2.0 channels (OCFG = 00) PWM slots

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/817b7175fef670d83dd4b9644758a0913f4941aa9797e4244c20e61620903273.jpg)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/b564250d39d8210ec643d1b4c6dec12760ff7f28de1e4badf5c75e8a00417f18.jpg)

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/2e9e6f8b7f88b8c250454b4245ca351c6ffcf9816a6b193892b831d9b591e00b.jpg)

AM045190v1

# 2.1 channels, two half-bridges + one full-bridge (OCFG = 01)

- FFX1A -> OUT1A  
FFX2A->OUT1B  
FFX3A->OUT2A  
FFX3B->OUT2B  
- FFX1A -> OUT3A  
- FFX1B -> OUT3B  
- FFX2A -> OUT4A  
FFX2B->OUT4B  
- FFX1A/1B configured as binary  
- FFX2A/2B configured as binary  
- FFX3A/3B configured as binary  
- FFX4A/4B is not used

In this configuration, channel 3 has full control (volume, EQ, etc...). On OUT3/OUT4 channels the channel 1 and channel 2 PWM are replicated.

In this configuration the PWM slot phase is the following as shown in Figure 29.

Figure 29. 2.1 channels (OCFG = 01) PWM slots  
![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/c60c2114d0a098d5740f218cd8c803e06f6107e7f6ec25fc724faeffee583c12.jpg)  
AM045191v1

# 2.1 channels, two full-bridge + one external full-bridge (OCFG = 10)

- FFX1A -> OUT1A  
- FFX1B -> OUT1B  
FFX2A->OUT2A  
FFX2B->OUT2B  
FFX3A->OUT3A  
FFX3B->OUT3B  
EAPD -> OUT4A  
- TWARN -> OUT4B  
- FFX1A/1B configured as ternary  
- FFX2A/2B configured as ternary  
- FFX3A/3B configured as ternary  
- FFX4A/4B is not used

In this configuration, channel 3 has full control (volume, EQ, etc...). On OUT4 channel the external bridge control signals are muxed.

In this configuration the PWM slot phase is shown in Figure 30.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/7a39206a9b34025782991f9342d3b5148dc9568ba559417322b58a9dc6d9db97.jpg)  
Figure 30. 2.1 channels (OCFG = 10) PWM slots

# 8.6.2 Invalid input detect mute enable

Table 45. Invalid input detect mute enable  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>2</td><td>R/W</td><td>1</td><td>IDE</td><td>Setting of 1 enables the automatic invalid input detect mute</td></tr></table>

Setting the IDE bit enables this function, which looks at the input  $I^2 S$  data and automatically mutes if the signals are perceived as invalid.

# 8.6.3 Binary output mode clock loss detection

Table 46. Binary output mode clock loss detection  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>3</td><td>R/W</td><td>1</td><td>BCLE</td><td>Binary output mode clock loss detection enable</td></tr></table>

The BCLE bit detects loss of input MCLK in binary mode and outputs  $50\%$  duty cycle.

# 8.6.4 LRCK double trigger protection

Table 47. LRCK double trigger protection  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>4</td><td>R/W</td><td>1</td><td>LDTE</td><td>LRCLK double trigger protection enable</td></tr></table>

The LDTE bit actively prevents double triggering of the LRCLK.

# 8.6.5 Auto EAPD on clock loss

Table 48. Auto EAPD on clock loss  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>5</td><td>R/W</td><td>0</td><td>ECLE</td><td>Auto EAPD on clock loss</td></tr></table>

When active, the ECLE bit issues a power device power-down signal (EAPD) on clock loss detection.

# 8.6.6 IC power-down

Table 49. IC power-down  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R/W</td><td>1</td><td>PWDN</td><td>0: IC power-down low-power condition
1: IC normal operation</td></tr></table>

The PWDN register is used to place the IC in a low-power state. When PWDN is written as 0, the output begins a soft-mute. After the mute condition is reached, EAPD is asserted

to power down the power-stage, then the master clock to all internal hardware except the  $\mathrm{I}^2\mathrm{C}$  block is gated. This places the IC in a very low power consumption state.

# 8.6.7 External amplifier power-down

Table 50. External amplifier power-down  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R/W</td><td>0</td><td>EAPD</td><td>0: External power stage power down active
1: Normal operation</td></tr></table>

The EAPD register directly disables/enables the internal power circuitry.

When EAPD = 0, the internal power section is placed in a low-power state (disabled). This register also controls the FFX4B/EAPD output pin when OCFG = 10.

# 8.7 Volume control registers (addr 0x06 - 0x0A)

# 8.7.1 Mute/line output configuration register

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>LOC1</td><td>LOC0</td><td>Reserved</td><td>Reserved</td><td>C3M</td><td>C2M</td><td>C1M</td><td>MMUTE</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

Table 51. Line output configuration  

<table><tr><td>LOC[1:0]</td><td>Line output configuration</td></tr><tr><td>00</td><td>Line output fixed - no volume, no EQ</td></tr><tr><td>01</td><td>Line output variable - CH3 volume effects line output, no EQ</td></tr><tr><td>10</td><td>Line output variable with EQ - CH3 volume effects line output</td></tr></table>

Line output is active when OCFG = 00 only. In this case LOC determines the line output configuration. The source of the line output is always the channel 1 and 2 inputs.

# 8.7.2 Master volume register

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>MV7</td><td>MV6</td><td>MV5</td><td>MV4</td><td>MV3</td><td>MV2</td><td>MV1</td><td>MV0</td></tr><tr><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td></tr></table>

# 8.7.3 Channel 1 volume

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C1V7</td><td>C1V6</td><td>C1V5</td><td>C1V4</td><td>C1V3</td><td>C1V2</td><td>C1V1</td><td>C1V0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.7.4 Channel 2 volume

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C2V7</td><td>C2V6</td><td>C2V5</td><td>C2V4</td><td>C2V3</td><td>C2V2</td><td>C2V1</td><td>C2V0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.7.5 Channel 3 / line output volume

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C3V7</td><td>C3V6</td><td>C3V5</td><td>C3V4</td><td>C3V3</td><td>C3V2</td><td>C3V1</td><td>C3V0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

The volume structure of the STA350Bx consists of individual volume registers for each channel and a master volume register that provides an offset to each channel volume setting. The individual channel volumes are adjustable in 0.5 dB steps from +48 dB to -80 dB.

As an example if  $C3V = 0 \times 00$  or  $+48$  dB and  $MV = 0 \times 18$  or  $-12$  dB, then the total gain for channel  $3 = +36$  dB.

The master mute, when set to 1, mutes all channels at once, whereas the individual channel mute (CxM) mutes only that channel. Both the master mute and the channel mutes provide a "soft mute" with the volume ramping down to mute in 4096 samples from the maximum volume setting at the internal processing rate (approximately  $96\mathrm{kHz}$ ).

A "hard (instantaneous) mute" can be obtained by programming a value of 0xFF (255) to any channel volume register or the master volume register. When volume offsets are provided via the master volume register, any channel whose total volume is less than -80 dB is muted.

All changes in volume take place at zero-crossings when ZCE = 1 (Configuration register E (addr 0x04)) on a per channel basis as this creates the smoothest possible volume transitions. When ZCE = 0, volume updates occur immediately.

Table 52. Master volume offset as a function of MV[7:0]  

<table><tr><td>MV[7:0]</td><td>Volume offset from channel value</td></tr><tr><td>00000000 (0x00)</td><td>0 dB</td></tr><tr><td>00000001 (0x01)</td><td>-0.5 dB</td></tr><tr><td>00000010 (0x02)</td><td>-1 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>01001100 (0x4C)</td><td>-38 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>11111110 (0xFE)</td><td>-127.5 dB</td></tr><tr><td>11111111 (0xFF)</td><td>Hard master mute</td></tr></table>

Table 53. Channel volume as a function of CxV[7:0]  

<table><tr><td>CxV[7:0]</td><td>Volume</td></tr><tr><td>00000000 (0x00)</td><td>+48 dB</td></tr><tr><td>00000001 (0x01)</td><td>+47.5 dB</td></tr><tr><td>00000010 (0x02)</td><td>+47 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>0101111 (0x5F)</td><td>+0.5 dB</td></tr><tr><td>01100000 (0x60)</td><td>0 dB</td></tr><tr><td>01100001 (0x61)</td><td>-0.5 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>11010111 (0xD7)</td><td>-59.5 dB</td></tr><tr><td>11011000 (0xD8)</td><td>-60 dB</td></tr><tr><td>11011001 (0xD9)</td><td>-61 dB</td></tr><tr><td>11011010 (0xCD)</td><td>-62 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>11101100 (0xEC)</td><td>-80 dB</td></tr><tr><td>11101101 (0xED)</td><td>Hard channel mute</td></tr><tr><td>...</td><td>...</td></tr><tr><td>11111111 (0xFF)</td><td>Hard channel mute</td></tr></table>

# 8.8 Audio preset registers (addr 0x0B and 0x0C)

# 8.8.1 Audio preset register 1 (addr 0x0B)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>Reserved</td><td>Reserved</td><td>AMGC[1]</td><td>AMGC[0]</td><td>Reserved</td><td>Reserved</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

Using AMGC[3:0] bits, attack and release thresholds and rates are automatically configured to properly fit application specific configurations. AMGC[3:2] is defined in register EQ coefficients and DRC configuration register (addr 0x31) on page 75.

The AMGC[1:0] bits behave in two different ways depending on the value of AMGC[3:2]. When this value is 00, then bits AMGC[1:0] are defined in Table 54.

Table 54. Audio preset gain compression/limiters selection for AMGC[3:2] = 00  

<table><tr><td>AMGC[1:0]</td><td>Mode</td></tr><tr><td>00</td><td>User-programmable GC</td></tr><tr><td>01</td><td>AC no clipping 2.1</td></tr><tr><td>10</td><td>AC limited clipping (10%) 2.1</td></tr><tr><td>11</td><td>DRC nighttime listening mode 2.1</td></tr></table>

# 8.8.2 Audio preset register 2 (addr 0x0C)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>XO3</td><td>XO2</td><td>XO1</td><td>XO0</td><td>AMAM2</td><td>AMAM1</td><td>AMAM0</td><td>AMAME</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.8.3 AM interference frequency switching

Table 55. AM interference frequency switching bits  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>0</td><td>R/W</td><td>0</td><td>AMAME</td><td>Audio preset AM enable
0: switching frequency determined by PWMS setting
1: switching frequency determined by AMAM settings</td></tr></table>

Table 56. Audio preset AM switching frequency selection  

<table><tr><td>AMAM[2:0]</td><td>48 kHz/96 kHz input fs</td><td>44.1 kHz/88.2 kHz input fs</td></tr><tr><td>000</td><td>0.535 MHz - 0.720 MHz</td><td>0.535 MHz - 0.670 MHz</td></tr><tr><td>001</td><td>0.721 MHz - 0.900 MHz</td><td>0.671 MHz - 0.800 MHz</td></tr><tr><td>010</td><td>0.901 MHz - 1.100 MHz</td><td>0.801 MHz - 1.000 MHz</td></tr><tr><td>011</td><td>1.101 MHz - 1.300 MHz</td><td>1.001 MHz - 1.180 MHz</td></tr><tr><td>100</td><td>1.301 MHz - 1.480 MHz</td><td>1.181 MHz - 1.340 MHz</td></tr><tr><td>101</td><td>1.481 MHz - 1.600 MHz</td><td>1.341 MHz - 1.500 MHz</td></tr><tr><td>110</td><td>1.601 MHz - 1.700 MHz</td><td>1.501 MHz - 1.700 MHz</td></tr></table>

# 8.8.4 Bass management crossover

Table 57. Bass management crossover  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>4</td><td>R/W</td><td>0</td><td>XO0</td><td rowspan="4">Selects the bass-management cross-over frequency. A 1st-order hign-pass filter (channels 1 and 2) or a 2nd-order low-pass filter (channel 3) at the selected frequency is performed.</td></tr><tr><td>5</td><td>R/W</td><td>0</td><td>XO1</td></tr><tr><td>6</td><td>R/W</td><td>0</td><td>XO2</td></tr><tr><td>7</td><td>R/W</td><td>0</td><td>XO3</td></tr></table>

Table 58. Bass management crossover frequency  

<table><tr><td>XO[3:0]</td><td>Crossover frequency</td></tr><tr><td>0000</td><td>User-defined</td></tr><tr><td>0001</td><td>80 Hz</td></tr><tr><td>0010</td><td>100 Hz</td></tr><tr><td>0011</td><td>120 Hz</td></tr></table>

Table 58. Bass management crossover frequency (continued)  

<table><tr><td>XO[3:0]</td><td>Crossover frequency</td></tr><tr><td>0100</td><td>140 Hz</td></tr><tr><td>0101</td><td>160 Hz</td></tr><tr><td>0110</td><td>180 Hz</td></tr><tr><td>0111</td><td>200 Hz</td></tr><tr><td>1000</td><td>220 Hz</td></tr><tr><td>1001</td><td>240 Hz</td></tr><tr><td>1010</td><td>260 Hz</td></tr><tr><td>1011</td><td>280 Hz</td></tr><tr><td>1100</td><td>300 Hz</td></tr><tr><td>1101</td><td>320 Hz</td></tr><tr><td>1110</td><td>340 Hz</td></tr><tr><td>1111</td><td>360 Hz</td></tr></table>

# 8.9 Channel configuration registers (addr 0x0E - 0x10)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C1OM1</td><td>C1OM0</td><td>C1LS1</td><td>C1LS0</td><td>C1BO</td><td>C1VPB</td><td>C1EQBP</td><td>C1TCB</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C2OM1</td><td>C2OM0</td><td>C2LS1</td><td>C2LS0</td><td>C2BO</td><td>C2VPB</td><td>C2EQBP</td><td>C2TCB</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C3OM1</td><td>C3OM0</td><td>C3LS1</td><td>C3LS0</td><td>C3BO</td><td>C3VPB</td><td>Reserved</td><td>Reserved</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.9.1 Tone control bypass

Tone control (bass/treble) can be bypassed on a per-channel basis for channels 1 and 2.

Table 59. Tone control bypass  

<table><tr><td>CxTCB</td><td>Mode</td></tr><tr><td>0</td><td>Perform tone control on channel x - normal operation</td></tr><tr><td>1</td><td>Bypass tone control on channel x</td></tr></table>

# 8.9.2 EQ bypass

EQ control can be bypassed on a per-channel basis for channels 1 and 2. If EQ control is bypassed on a given channel, the prescale and all filters (high-pass, biquads, de-emphasis, bass, treble in any combination) are bypassed for that channel.

Table 60. EQ bypass  

<table><tr><td>CxEQBP</td><td>Mode</td></tr><tr><td>0</td><td>Perform EQ on channel x - normal operation</td></tr><tr><td>1</td><td>Bypass EQ on channel x</td></tr></table>

# 8.9.3 Volume bypass

Each channel contains an individual channel volume bypass. If a particular channel has volume bypassed via the CxVBP = 1 register then only the channel volume setting for that particular channel affects the volume setting, the master volume setting does not affect that channel.

# 8.9.4 Binary output enable registers

Each individual channel output can be set to output a binary PWM stream. In this mode output A of a channel is considered the positive output and output B is the negative inverse.

Table 61. Binary output enable registers  

<table><tr><td>CxBO</td><td>Mode</td></tr><tr><td>0</td><td>FFX 3-state output - normal operation</td></tr><tr><td>1</td><td>Binary output</td></tr></table>

# 8.9.5 Limiter select

Limiter selection can be made on a per-channel basis according to the channel limiter select bits.

Table 62. Channel limiter mapping as a function of CxLS bits  

<table><tr><td>CxLS[1:0]</td><td>Channel limiter mapping</td></tr><tr><td>00</td><td>Channel has limiting disabled</td></tr><tr><td>01</td><td>Channel is mapped to limiter #1</td></tr><tr><td>10</td><td>Channel is mapped to limiter #2</td></tr></table>

# 8.9.6 Output mapping

Output mapping can be performed on a per channel basis according to the CxOM channel output mapping bits. Each input into the output configuration engine can receive data from any of the three processing channel outputs.

Table 63. Channel output mapping as a function of CxOM bits  

<table><tr><td>CxOM[1:0]</td><td>Channel x output source from</td></tr><tr><td>00</td><td>Channel1</td></tr><tr><td>01</td><td>Channel 2</td></tr><tr><td>10</td><td>Channel 3</td></tr></table>

# 8.10 Tone control register (addr 0x11)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>TTC3</td><td>TTC2</td><td>TTC1</td><td>TTC0</td><td>BTC3</td><td>BTC2</td><td>BTC1</td><td>BTC0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td></tr></table>

# 8.10.1 Tone control

Table 64. Tone control boost/cut as a function of BTC and TTC bits  

<table><tr><td>BTC[3:0]/TTC[3:0]</td><td>Boost/cut</td></tr><tr><td>0000</td><td>-12 dB</td></tr><tr><td>0001</td><td>-12 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>0111</td><td>-4 dB</td></tr><tr><td>0110</td><td>-2 dB</td></tr><tr><td>0111</td><td>0 dB</td></tr><tr><td>1000</td><td>+2 dB</td></tr><tr><td>1001</td><td>+4 dB</td></tr><tr><td>...</td><td>...</td></tr><tr><td>1101</td><td>+12 dB</td></tr><tr><td>1110</td><td>+12 dB</td></tr><tr><td>1111</td><td>+12 dB</td></tr></table>

# 8.11 Dynamic control registers (addr 0x12 - 0x15)

# 8.11.1 Limiter 1 attack/release rate

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>L1A3</td><td>L1A2</td><td>L1A1</td><td>L1A0</td><td>L1R3</td><td>L1R2</td><td>L1R1</td><td>L1R0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>0</td></tr></table>

# 8.11.2 Limiter 1 attack/release threshold

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>L1AT3</td><td>L1AT2</td><td>L1AT1</td><td>L1AT0</td><td>L1RT3</td><td>L1RT2</td><td>L1RT1</td><td>L1RT0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td></tr></table>

# 8.11.3 Limiter 2 attack/release rate

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>L2A3</td><td>L2A2</td><td>L2A1</td><td>L2A0</td><td>L2R3</td><td>L2R2</td><td>L2R1</td><td>L2R0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>0</td></tr></table>

# 8.11.4 Limiter 2 attack/release threshold

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>L2AT3</td><td>L2AT2</td><td>L2AT1</td><td>L2AT0</td><td>L2RT3</td><td>L2RT2</td><td>L2RT1</td><td>L2RT0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td></tr></table>

The STA350Bx includes two independent limiter blocks. The purpose of the limiters is to automatically reduce the dynamic range of a recording to prevent the outputs from clipping in anti-clipping mode or to actively reduce the dynamic range for a better listening environment such as a night-time listening mode which is often needed for DVDs. The two modes are selected via the DRC bit in Configuration register E (addr 0x04) on page 46. Each channel can be mapped to either limiter or not mapped, meaning that the channel clips when 0 dBfs is exceeded. Each limiter looks at the present value of each channel that is mapped to it, selects the maximum absolute value of all these channels, performs the limiting algorithm on that value, and then if needed adjusts the gain of the mapped channels in unison.

The limiter attack thresholds are determined by the LxAT registers if EATHx[7] bits are set to 0 else the thresholds are determined by EATHx[6:0]. It is recommended in anti-clipping mode to set this to 0 dBfs, which corresponds to the maximum unclipped output power of an FFX amplifier. Since gain can be added digitally within the STA350Bx, it is possible to exceed 0 dBfs or any other LxAT setting. When this occurs, the limiter, when active, automatically starts reducing the gain. The rate at which the gain is reduced when the attack threshold is exceeded is dependent upon the attack rate register setting for that limiter. Gain reduction occurs on a peak-detect algorithm. Setting the EATHx[7] bits to 1 selects the anti-clipping mode.

The limiter release thresholds are determined by the LxRT registers if ERTHx[7] bits are set to 0, else the thresholds are determined by ERTHx[6:0]. Setting the ERTHx[7] bits to 1 automatically selects the anti-clipping mode. The release of the limiter, when the gain is again increased, is dependent on an RMS-detect algorithm. The output of the volume/limiter block is passed through an RMS filter. The output of this filter is compared to the release threshold, determined by the Release Threshold register. When the RMS filter output falls below the release threshold, the gain is again increased at a rate dependent upon the Release rate register. The gain can never be increased past its set value and, therefore, the release only occurs if the limiter has already reduced the gain. The release threshold value can be used to set what is effectively a minimum dynamic range, this is helpful as overlimiting can reduce the dynamic range to virtually zero and cause program material to sound "lifeless".

In AC mode, the attack and release thresholds are set relative to full-scale. In DRC mode, the attack threshold is set relative to the maximum volume setting of the channels mapped to that limiter and the release threshold is set relative to the maximum volume setting plus the attack threshold.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/a7aa8bc68b09b39169503825024df6fa72f430af7825608c061ca40c241b22c7.jpg)  
Figure 31. Basic limiter and volume flow diagram

Table 65. Limiter attack rate as a function of LxA bits  

<table><tr><td>LxA[3:0]</td><td>Attack rate dB/ms</td><td></td></tr><tr><td>0000</td><td>3.1584</td><td rowspan="16">Fast</td></tr><tr><td>0001</td><td>2.7072</td></tr><tr><td>0010</td><td>2.2560</td></tr><tr><td>0011</td><td>1.8048</td></tr><tr><td>0100</td><td>1.3536</td></tr><tr><td>0101</td><td>0.9024</td></tr><tr><td>0110</td><td>0.4512</td></tr><tr><td>0111</td><td>0.2256</td></tr><tr><td>1000</td><td>0.1504</td></tr><tr><td>1001</td><td>0.1123</td></tr><tr><td>1010</td><td>0.0902</td></tr><tr><td>1011</td><td>0.0752</td></tr><tr><td>1100</td><td>0.0645</td></tr><tr><td>1101</td><td>0.0564</td></tr><tr><td>1110</td><td>0.0501</td></tr><tr><td>1111</td><td>0.0451</td></tr></table>

Table 66. Limiter release rate as a function of LxR bits  

<table><tr><td>LxR[3:0]</td><td>Release rate dB/ms</td><td></td></tr><tr><td>0000</td><td>0.5116</td><td rowspan="16">Fast</td></tr><tr><td>0001</td><td>0.1370</td></tr><tr><td>0010</td><td>0.0744</td></tr><tr><td>0011</td><td>0.0499</td></tr><tr><td>0100</td><td>0.0360</td></tr><tr><td>0101</td><td>0.0299</td></tr><tr><td>0110</td><td>0.0264</td></tr><tr><td>0111</td><td>0.0208</td></tr><tr><td>1000</td><td>0.0198</td></tr><tr><td>1001</td><td>0.0172</td></tr><tr><td>1010</td><td>0.0147</td></tr><tr><td>1011</td><td>0.0137</td></tr><tr><td>1100</td><td>0.0134</td></tr><tr><td>1101</td><td>0.0117</td></tr><tr><td>1110</td><td>0.0110</td></tr><tr><td>1111</td><td>0.0104</td></tr></table>

# Anti-clipping mode

Table 67. Limiter attack threshold as a function of LxAT bits (AC-mode)  

<table><tr><td>LxAT[3:0]</td><td>AC (dB relative to fs)</td></tr><tr><td>0000</td><td>-12</td></tr><tr><td>0001</td><td>-10</td></tr><tr><td>0010</td><td>-8</td></tr><tr><td>0011</td><td>-6</td></tr><tr><td>0100</td><td>-4</td></tr><tr><td>0101</td><td>-2</td></tr><tr><td>0110</td><td>0</td></tr><tr><td>0111</td><td>+2</td></tr><tr><td>1000</td><td>+3</td></tr><tr><td>1001</td><td>+4</td></tr><tr><td>1010</td><td>+5</td></tr><tr><td>1011</td><td>+6</td></tr><tr><td>1100</td><td>+7</td></tr><tr><td>1101</td><td>+8</td></tr><tr><td>1110</td><td>+9</td></tr><tr><td>1111</td><td>+10</td></tr></table>

Table 68. Limiter release threshold as a function of LxRT bits (AC-mode)  

<table><tr><td>LxRT[3:0]</td><td>AC (dB relative to fs)</td></tr><tr><td>0000</td><td>-∞</td></tr><tr><td>0001</td><td>-29 dB</td></tr><tr><td>0010</td><td>-20 dB</td></tr><tr><td>0011</td><td>-16 dB</td></tr><tr><td>0100</td><td>-14 dB</td></tr><tr><td>0101</td><td>-12 dB</td></tr><tr><td>0110</td><td>-10 dB</td></tr><tr><td>0111</td><td>-8 dB</td></tr><tr><td>1000</td><td>-7 dB</td></tr><tr><td>1001</td><td>-6 dB</td></tr><tr><td>1010</td><td>-5 dB</td></tr><tr><td>1011</td><td>-4 dB</td></tr><tr><td>1100</td><td>-3 dB</td></tr><tr><td>1101</td><td>-2 dB</td></tr><tr><td>1110</td><td>-1 dB</td></tr><tr><td>1111</td><td>-0 dB</td></tr></table>

# Dynamic range compression mode

Table 69. Limiter attack threshold as a function of LxAT bits (DRC -mode)  

<table><tr><td>LxAT[3:0]</td><td>DRC (dB relative to Volume)</td></tr><tr><td>0000</td><td>-31</td></tr><tr><td>0001</td><td>-29</td></tr><tr><td>0010</td><td>-27</td></tr><tr><td>0011</td><td>-25</td></tr><tr><td>0100</td><td>-23</td></tr><tr><td>0101</td><td>-21</td></tr><tr><td>0110</td><td>-19</td></tr><tr><td>0111</td><td>-17</td></tr><tr><td>1000</td><td>-16</td></tr><tr><td>1001</td><td>-15</td></tr><tr><td>1010</td><td>-14</td></tr><tr><td>1011</td><td>-13</td></tr><tr><td>1100</td><td>-12</td></tr><tr><td>1101</td><td>-10</td></tr><tr><td>1110</td><td>-7</td></tr><tr><td>1111</td><td>-4</td></tr></table>

Table 70. Limiter release threshold as a as a function of LxRT bits (DRC-mode)  

<table><tr><td>LxRT[3:0]</td><td>DRC (db relative to Volume + LxAT)</td></tr><tr><td>0000</td><td>-∞</td></tr><tr><td>0001</td><td>-38 dB</td></tr><tr><td>0010</td><td>-36 dB</td></tr><tr><td>0011</td><td>-33 dB</td></tr><tr><td>0100</td><td>-31 dB</td></tr><tr><td>0101</td><td>-30 dB</td></tr><tr><td>0110</td><td>-28 dB</td></tr><tr><td>0111</td><td>-26 dB</td></tr><tr><td>1000</td><td>-24 dB</td></tr><tr><td>1001</td><td>-22 dB</td></tr><tr><td>1010</td><td>-20 dB</td></tr><tr><td>1011</td><td>-18 dB</td></tr><tr><td>1100</td><td>-15 dB</td></tr><tr><td>1101</td><td>-12 dB</td></tr><tr><td>1110</td><td>-9 dB</td></tr><tr><td>1111</td><td>-6 dB</td></tr></table>

# 8.11.5 Limiter 1 extended attack threshold (addr 0x32)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>EATHEN1</td><td>EATH1[6]</td><td>EATH1[5]</td><td>EATH1[4]</td><td>EATH1[3]</td><td>EATH1[2]</td><td>EATH1[1]</td><td>EATH1[0]</td></tr><tr><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td></tr></table>

The extended attack threshold value is determined as follows: attack threshold = -12 + EATH1 / 4

# 8.11.6 Limiter 1 extended release threshold (addr 0x33)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>ERTHEN1</td><td>ERTH1[6]</td><td>ERTH1[5]</td><td>ERTH1[4]</td><td>ERTH1[3]</td><td>ERTH1[2]</td><td>ERTH1[1]</td><td>ERTH1[0]</td></tr><tr><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td></tr></table>

The extended release threshold value is determined as follows: release threshold  $= -12 + \text{ERTH1} / 4$

# 8.11.7 Limiter 2 extended attack threshold (addr 0x34)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>EATHEN2</td><td>EATH2[6]</td><td>EATH2[5]</td><td>EATH2[4]</td><td>EATH2[3]</td><td>EATH2[2]</td><td>EATH2[1]</td><td>EATH2[0]</td></tr><tr><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td></tr></table>

The extended attack threshold value is determined as follows:

attack threshold = -12 + EATH2 / 4

# 8.11.8 Limiter 2 extended release threshold (addr 0x35)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>ERTHEN2</td><td>ERTH2[6]</td><td>ERTH2[5]</td><td>ERTH2[4]</td><td>ERTH2[3]</td><td>ERTH2[2]</td><td>ERTH2[1]</td><td>ERTH2[0]</td></tr><tr><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td><td>TBD</td></tr></table>

The extended release threshold value is determined as follows:

release threshold  $= -12 +$  ERTH2 / 4

Note: Attack/release threshold step is 0.125 dB in the range -12 dB to 0 dB.

# 8.12 User-defined coefficient control registers (addr 0x16 - 0x26)

# 8.12.1 Coefficient address register

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td></td><td></td><td>CFA5</td><td>CFA4</td><td>CFA3</td><td>CFA2</td><td>CFA1</td><td>CFA0</td></tr><tr><td></td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.2 Coefficient b1 data register bits 23:16

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C1B23</td><td>C1B22</td><td>C1B21</td><td>C1B20</td><td>C1B19</td><td>C1B18</td><td>C1B17</td><td>C1B16</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.3 Coefficient b1 data register bits 15:8

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C1B15</td><td>C1B14</td><td>C1B13</td><td>C1B12</td><td>C1B11</td><td>C1B10</td><td>C1B9</td><td>C1B8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.4 Coefficient b1 data register bits 7:0

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C1B7</td><td>C1B6</td><td>C1B5</td><td>C1B4</td><td>C1B3</td><td>C1B2</td><td>C1B1</td><td>C1B0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.5 Coefficient b2 data register bits 23:16

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C2B23</td><td>C2B22</td><td>C2B21</td><td>C2B20</td><td>C2B19</td><td>C2B18</td><td>C2B17</td><td>C2B16</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.6 Coefficient b2 data register bits 15:8

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C2B15</td><td>C2B14</td><td>C2B13</td><td>C2B12</td><td>C2B11</td><td>C2B10</td><td>C2B9</td><td>C2B8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.7 Coefficient b2 data register bits 7:0

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C2B7</td><td>C2B6</td><td>C2B5</td><td>C2B4</td><td>C2B3</td><td>C2B2</td><td>C2B1</td><td>C2B0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.8 Coefficient a1 data register bits 23:16

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C1B23</td><td>C1B22</td><td>C1B21</td><td>C1B20</td><td>C1B19</td><td>C1B18</td><td>C1B17</td><td>C1B16</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.9 Coefficient a1 data register bits 15:8

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C3B15</td><td>C3B14</td><td>C3B13</td><td>C3B12</td><td>C3B11</td><td>C3B10</td><td>C3B9</td><td>C3B8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.10 Coefficient a1 data register bits 7:0

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C3B7</td><td>C3B6</td><td>C3B5</td><td>C3B4</td><td>C3B3</td><td>C3B2</td><td>C3B1</td><td>C3B0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.11 Coefficient a2 data register bits 23:16

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C4B23</td><td>C4B22</td><td>C4B21</td><td>C4B20</td><td>C4B19</td><td>C4B18</td><td>C4B17</td><td>C4B16</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.12 Coefficient a2 data register bits 15:8

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C4B15</td><td>C4B14</td><td>C4B13</td><td>C4B12</td><td>C4B11</td><td>C4B10</td><td>C4B9</td><td>C4B8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.13 Coefficient a2 data register bits 7:0

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C4B7</td><td>C4B6</td><td>C4B5</td><td>C4B4</td><td>C4B3</td><td>C4B2</td><td>C4B1</td><td>C4B0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.14 Coefficient b0 data register bits 23:16

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C5B23</td><td>C5B22</td><td>C5B21</td><td>C5B20</td><td>C5B19</td><td>C5B18</td><td>C5B17</td><td>C5B16</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.15 Coefficient b0 data register bits 15:8

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C5B15</td><td>C5B14</td><td>C5B13</td><td>C5B12</td><td>C5B11</td><td>C5B10</td><td>C5B9</td><td>C5B8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.16 Coefficient b0 data register bits 7:0

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>C5B7</td><td>C5B6</td><td>C5B5</td><td>C5B4</td><td>C5B3</td><td>C5B2</td><td>C5B1</td><td>C5B0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.12.17 Coefficient write/read control register

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td colspan="4">Reserved</td><td>RA</td><td>R1</td><td>WA</td><td>W1</td></tr><tr><td colspan="4">0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

Coefficients for user-defined EQ, mixing, scaling, and bass management are handled internally in the STA350Bx via RAM. Access to this RAM is available to the user via an I²C register interface. A collection of I²C registers are dedicated to this function. One contains a coefficient base address, five sets of three store the values of the 24-bit coefficients to be written or that were read, and one contains bits used to control the write/read of the coefficient(s) to/from RAM.

Three different RAM banks are embedded in the STA350Bx. The three banks are managed in paging mode using EQCFG register bits. They can be used to store different EQ settings. For speaker frequency compensation, a sampling frequency independent EQ must be implemented. Computing three different coefficients set for  $32\mathrm{kHz}$ ,  $44.1\mathrm{kHz}$ ,  $48\mathrm{kHz}$  and downloading them into the three RAM banks, it is possible to select the suitable RAM block depending on the incoming frequency with a simple I²C write operation in register 0x31.

For example, in case of different input sources (different sampling rates), the three different sets of coefficients can be downloaded once at startup, and during normal play it is possible to switch among the three RAM blocks allowing faster operation, without any additional download from the microcontroller.

To write the coefficients in a particular RAM bank, this bank must be selected first, writing bit 0 and bit 1 in register  $0 \times 31$ . Then the write procedure below can be used.

Note that as soon as a RAM bank is selected, the EQ settings are automatically switched to the coefficients stored in the active RAM block.

Note:

The read write operation on RAM coefficients works only if RLCKI (pin29) is switching and stable (ref. Table 7, tLRJT timing) and PLL must be locked (ref bit D7 reg 0x2D).

# Reading a coefficient from RAM

1. Select the RAM block with register 0x31 bit 1, bit 0.  
2. Write 6 bits of address to  $\mathrm{I}^2\mathrm{C}$  register  $0\times 16$  
3. Write 1 to R1 bit in  $I^2C$  address 0x26.  
4. Read top 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x17.  
5. Read middle 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x18.  
6. Read bottom 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x19.

# Reading a set of coefficients from RAM

1. Select the RAM block with register 0x31 bit1, bit0.  
2. Write 6 bits of address to  $\mathrm{I}^2\mathrm{C}$  register 0x16.  
3. Write 1 to RA bit in  $I^2C$  address 0x26.  
4. Read top 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x17.  
5. Read middle 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x18.  
6. Read bottom 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x19.  
7. Read top 8 bits of coefficient b2 in  $\mathrm{I}^2\mathrm{C}$  address 0x1A.  
8. Read middle 8 bits of coefficient b2 in  $\mathrm{I}^2\mathrm{C}$  address 0x1B.  
9. Read bottom 8 bits of coefficient b2 in  $\mathrm{I}^2\mathrm{C}$  address 0x1C.  
10. Read top 8 bits of coefficient a1 in  $\mathrm{I}^2\mathrm{C}$  address 0x1D.  
11. Read middle 8 bits of coefficient a1 in  $\mathrm{I}^2\mathrm{C}$  address 0x1E.  
12. Read bottom 8 bits of coefficient a1 in  $\mathrm{I}^2\mathrm{C}$  address 0x1F.  
13. Read top 8 bits of coefficient a2 in  $I^2C$  address 0x20.  
14. Read middle 8 bits of coefficient a2 in  $\mathrm{I}^2\mathrm{C}$  address 0x21.  
15. Read bottom 8 bits of coefficient a2 in  $\mathrm{I}^2\mathrm{C}$  address 0x22.  
16. Read top 8 bits of coefficient b0 in  $I^2C$  address 0x23.  
17. Read middle 8 bits of coefficient b0 in  $\mathsf{I}^2\mathsf{C}$  address 0x24.  
18. Read bottom 8 bits of coefficient b0 in  $\mathrm{I}^2\mathrm{C}$  address 0x25.

# Writing a single coefficient to RAM

1. Select the RAM block with register 0x31 bit1, bit0.  
2. Write 6 bits of address to  $\mathrm{I}^2\mathrm{C}$  register  $0\times 16$  
3. Write top 8 bits of coefficient in  $\mathsf{I}^2\mathsf{C}$  address 0x17.  
4. Write middle 8 bits of coefficient in  $\mathrm{I}^2\mathrm{C}$  address 0x18.  
5. Write bottom 8 bits of coefficient in  $\mathrm{I}^{2}\mathrm{C}$  address 0x19.  
6. Write 1 to the W1 bit in  $I^2C$  address 0x26.

# Writing a set of coefficients to RAM

1. Select the RAM block with register 0x31 bit1, bit0.  
2. Write 6 bits of starting address to  $\mathrm{I}^2\mathrm{C}$  register  $0\times 16$  
3. Write top 8 bits of coefficient b1 in  $I^2C$  address 0x17.  
4. Write middle 8 bits of coefficient b1 in  $I^2C$  address 0x18.  
5. Write bottom 8 bits of coefficient b1 in  $\mathrm{I}^2\mathrm{C}$  address 0x19.  
6. Write top 8 bits of coefficient b2 in  $\mathrm{I}^2\mathrm{C}$  address 0x1A.  
7. Write middle 8 bits of coefficient b2 in  $\mathrm{I}^2\mathrm{C}$  address 0x1B.  
8. Write bottom 8 bits of coefficient b2 in  $\mathsf{l}^2\mathsf{C}$  address 0x1C.  
9. Write top 8 bits of coefficient a1 in  $\mathsf{I}^2\mathsf{C}$  address  $0x1D$  
10. Write middle 8 bits of coefficient a1 in  $\mathrm{I}^2\mathrm{C}$  address 0x1E.  
11. Write bottom 8 bits of coefficient a1 in  $\mathrm{I}^2\mathrm{C}$  address 0x1F.  
12. Write top 8 bits of coefficient a2 in  $I^2C$  address 0x20.  
13. Write middle 8 bits of coefficient a2 in  $\mathsf{I}^2\mathsf{C}$  address 0x21.  
14. Write bottom 8 bits of coefficient a2 in  $\mathrm{I}^2\mathrm{C}$  address 0x22.  
15. Write top 8 bits of coefficient b0 in  $\mathrm{I}^2\mathrm{C}$  address 0x23.  
16. Write middle 8 bits of coefficient b0 in  $\mathsf{I}^2\mathsf{C}$  address 0x24.  
17. Write bottom 8 bits of coefficient b0 in  $\mathsf{I}^2\mathsf{C}$  address 0x25.  
18. Write 1 to the WA bit in  $\mathrm{I}^2\mathrm{C}$  address  $0\times 26$

The mechanism for writing a set of coefficients to RAM provides a method of updating the five coefficients corresponding to a given biquad (filter) simultaneously to avoid possible unpleasant acoustic side-effects. When using this technique, the 6-bit address specifies the address of the biquad b1 coefficient (for example, 0, 5, 10, 20, 35 decimal), and the STA350Bx generates the RAM addresses as offsets from this base value to write the complete set of coefficient data.

# 8.12.18 User-defined EQ

The STA350Bx can be programmed for four EQ filters (biquads) per each of the two input channels. The biquads use the following equation:

$$
\begin{array}{l} Y [ n ] = 2 ^ {*} \left(b _ {0} / 2\right) ^ {*} X [ n ] + 2 ^ {*} \left(b _ {1} / 2\right) ^ {*} X [ n - 1 ] + b _ {2} ^ {*} X [ n - 2 ] - 2 ^ {*} \left(a _ {1} / 2\right) ^ {*} Y [ n - 1 ] - a _ {2} ^ {*} Y [ n - 2 ] \\ = b _ {0} ^ {*} X [ n ] + b _ {1} ^ {*} X [ n - 1 ] + b _ {2} ^ {*} X [ n - 2 ] - a _ {1} ^ {*} Y [ n - 1 ] - a _ {2} ^ {*} Y [ n - 2 ] \\ \end{array}
$$

where  $Y[n]$  represents the output and  $X[n]$  represents the input. Multipliers are 24-bit signed fractional multipliers, with coefficient values in the range of 0x800000 (-1) to 0x7FFFFFF (0.9999998808).

Coefficients stored in the user-defined coefficient RAM are referenced in the following manner:

$$
\mathrm {C x H y} 0 = \mathrm {b} _ {1} / 2
$$

$$
\mathrm {C x H y 1} = \mathrm {b} _ {2}
$$

$$
\mathrm {C x H y 2} = - \mathrm {a} _ {1} / 2
$$

$$
\mathrm {C x H y 3} = - \mathrm {a} _ {2}
$$

$$
\mathrm {C x H y 4} = \mathrm {b} _ {0} / 2
$$

where  $x$  represents the channel and the  $y$  the biquad number. For example, C2H41 is the  $b_{2}$  coefficient in the fourth biquad for channel 2.

Additionally, the STA350Bx can be programmed for a high-pass filter (processing channels 1 and 2) and a low-pass filter (processing channel 3) to be used for bass-management crossover when the XO setting is 000 (user-defined). Both of these filters when defined by the user (rather than using the preset crossover filters) are second order filters that use the biquad equation given above. They are loaded into the C12H0-4 and C3Hy0-4 areas of RAM noted in Table 71.

By default, all user-defined filters are pass-through where all coefficients are set to 0, except the  $b_0 / 2$  coefficient which is set to 0x400000 (representing 0.5).

# 8.12.19 Pre-scale

The STA350Bx provides a multiplication for each input channel for the purpose of scaling the input prior to EQ. This pre-EQ scaling is accomplished by using a 24-bit signed fractional multiplier, with  $0 \times 800000 = -1$  and  $0 \times 7FFFFFF = 0.9999998808$ . The scale factor for this multiplication is loaded into RAM using the same I²C registers as the biquad coefficients and the bass-management. All channels can use the channel-1 pre-scale factor by setting the Biquad link bit. By default, all pre-scale factors are set to 0x7FFFFFF.

# 8.12.20 Post-scale

The STA350Bx provides one additional multiplication after the last interpolation stage and the distortion compensation on each channel. This post-scaling is accomplished by using a 24-bit signed fractional multiplier, with  $0 \times 800000 = -1$  and  $0 \times 7FFFFFF = 0.9999998808$ . The scale factor for this multiplication is loaded into RAM using the same I²C registers as the biquad coefficients and the bass-management. This post-scale factor can be used in conjunction with an ADC equipped microcontroller to perform power-supply error correction. All channels can use the channel-1 post-scale factor by setting the post-scale link bit. By default, all post-scale factors are set to  $0 \times 7FFFFFF$ . When line output is being used, channel-3 post-scale will affect both channels 3 and 4.

# 8.12.21 Overcurrent post-scale

The STA350Bx provides a simple mechanism for reacting to overcurrent detection in the power block. When the ocwarn input is asserted, the overcurrent post-scale value is used in place of the normal post-scale value to provide output attenuation on all channels. The default setting provides 3 dB of output attenuation when ocwarn is asserted.

The amount of attenuation to be applied in this situation can be adjusted by modifying the overcurrent post-scale value. As with the normal post-scale, this scaling value is a 24-bit signed fractional multiplier, with  $0 \times 800000 = -1$  and  $0 \times 7FFFFFF = 0.9999998808$ . By default, the overcurrent post-scale factor is set to  $0 \times 5A9DF7$ . Once the overcurrent attenuation is applied, it remains until the device is reset.

Table 71. RAM block for biquads, mixing, scaling and bass management  

<table><tr><td>Index (decimal)</td><td>Index (hex)</td><td></td><td>Coefficient</td><td>Default</td></tr><tr><td>0</td><td>0x00</td><td rowspan="5">Channel 1 - biquad 1</td><td>C1H10(b1/2)</td><td>0x000000</td></tr><tr><td>1</td><td>0x01</td><td>C1H11(b2)</td><td>0x000000</td></tr><tr><td>2</td><td>0x02</td><td>C1H12(a1/2)</td><td>0x000000</td></tr><tr><td>3</td><td>0x03</td><td>C1H13(a2)</td><td>0x000000</td></tr><tr><td>4</td><td>0x04</td><td>C1H14(b0/2)</td><td>0x400000</td></tr><tr><td>5</td><td>0x05</td><td>Channel 1 - biquad 2</td><td>C1H20</td><td>0x000000</td></tr><tr><td>...</td><td>...</td><td>...</td><td>...</td><td>...</td></tr><tr><td>19</td><td>0x13</td><td>Channel 1 - biquad 4</td><td>C1H44</td><td>0x400000</td></tr><tr><td>20</td><td>0x14</td><td rowspan="2">Channel 2 - biquad 1</td><td>C2H10</td><td>0x000000</td></tr><tr><td>21</td><td>0x15</td><td>C2H11</td><td>0x000000</td></tr><tr><td>...</td><td>...</td><td>...</td><td>...</td><td>...</td></tr><tr><td>39</td><td>0x27</td><td>Channel 2 - biquad 4</td><td>C2H44</td><td>0x400000</td></tr><tr><td>40</td><td>0x28</td><td rowspan="5">Channel 1/2 - biquad 5 for XO = 000 Hi-pass 2nd Order filter for XO≠000</td><td>C12H0(b1/2)</td><td>0x000000</td></tr><tr><td>41</td><td>0x29</td><td>C12H1(b2)</td><td>0x000000</td></tr><tr><td>42</td><td>0x2A</td><td>C12H2(a1/2)</td><td>0x000000</td></tr><tr><td>43</td><td>0x2B</td><td>C12H3(a2)</td><td>0x000000</td></tr><tr><td>44</td><td>0x2C</td><td>C12H4(b0/2)</td><td>0x400000</td></tr><tr><td>45</td><td>0x2D</td><td rowspan="5">Channel 3 - biquad for XO = 000 Low-pass 2nd-order filter for XO≠000</td><td>C3H0(b1/2)</td><td>0x000000</td></tr><tr><td>46</td><td>0x2E</td><td>C3H1(b2)</td><td>0x000000</td></tr><tr><td>47</td><td>0x2F</td><td>C3H2(a1/2)</td><td>0x000000</td></tr><tr><td>48</td><td>0x30</td><td>C3H3(a2)</td><td>0x000000</td></tr><tr><td>49</td><td>0x31</td><td>C3H4(b0/2)</td><td>0x400000</td></tr><tr><td>50</td><td>0x32</td><td>Channel 1 - pre-scale</td><td>C1PreS</td><td>0x7FFFFFF</td></tr><tr><td>51</td><td>0x33</td><td>Channel 2 - pre-scale</td><td>C2PreS</td><td>0x7FFFFFF</td></tr><tr><td>52</td><td>0x34</td><td>Channel 1 - pre-scale</td><td>C1PstS</td><td>0x7FFFFFF</td></tr><tr><td>53</td><td>0x35</td><td>Channel 2 - pre-scale</td><td>C2PstS</td><td>0x7FFFFFF</td></tr></table>

Table 71. RAM block for biquads, mixing, scaling and bass management (continued)  

<table><tr><td>Index (decimal)</td><td>Index (hex)</td><td></td><td>Coefficient</td><td>Default</td></tr><tr><td>54</td><td>0x36</td><td>Channel 3 - post-scale</td><td>C3PstS</td><td>0x7FFFFFF</td></tr><tr><td>55</td><td>0x37</td><td>TWARN/OC - Limit</td><td>TWOCL</td><td>0x5A9DF7</td></tr><tr><td>56</td><td>0x38</td><td>Channel 1 - Mix 1</td><td>C1MX1</td><td>0x7FFFFFF</td></tr><tr><td>57</td><td>0x39</td><td>Channel 1 - Mix 2</td><td>C1MX2</td><td>0x000000</td></tr><tr><td>58</td><td>0x3A</td><td>Channel 2 - Mix 1</td><td>C2MX1</td><td>0x000000</td></tr><tr><td>59</td><td>0x3B</td><td>Channel 2 - Mix 2</td><td>C2MX2</td><td>0x7FFFFFF</td></tr><tr><td>60</td><td>0x3C</td><td>Channel 3 - Mix 1</td><td>C3MX1</td><td>0x400000</td></tr><tr><td>61</td><td>0x3D</td><td>Channel 3 - Mix 2</td><td>C3MX2</td><td>0x400000</td></tr><tr><td>62</td><td>0x3E</td><td>UNUSED</td><td></td><td></td></tr><tr><td>63</td><td>0x3F</td><td>UNUSED</td><td></td><td></td></tr></table>

# 8.13 Variable max. power correction registers (addr 0x27 - 0x28)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>MPCC15</td><td>MPCC14</td><td>MPCC13</td><td>MPCC12</td><td>MPCC11</td><td>MPCC10</td><td>MPCC9</td><td>MPCC8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>MPCC7</td><td>MPCC6</td><td>MPCC5</td><td>MPCC4</td><td>MPCC3</td><td>MPCC2</td><td>MPCC1</td><td>MPCC0</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

The MPCC bits determine the 16 MSBs of the MPC compensation coefficient. This coefficient is used in place of the default coefficient when MPCV = 1.

# 8.14 Variable distortion compensation registers (addr 0x29 - 0x2A)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>DCC15</td><td>DCC14</td><td>DCC13</td><td>DCC12</td><td>DCC11</td><td>DCC10</td><td>DCC9</td><td>DCC8</td></tr><tr><td>1</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>1</td><td>1</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>DCC7</td><td>DCC6</td><td>DCC5</td><td>DCC4</td><td>DCC3</td><td>DCC2</td><td>DCC1</td><td>DCC0</td></tr><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>1</td><td>1</td></tr></table>

The DCC bits determine the 16 MSBs of the distortion compensation coefficient. This coefficient is used in place of the default coefficient when DCCV = 1.

# 8.15 Fault detect recovery constant registers (addr 0x2B - 0x2C)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>FDRC15</td><td>FDRC14</td><td>FDRC13</td><td>FDRC12</td><td>FDRC11</td><td>FDRC10</td><td>FDRC9</td><td>FDRC8</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>FDRC7</td><td>FDRC6</td><td>FDRC5</td><td>FDRC4</td><td>FDRC3</td><td>FDRC2</td><td>FDRC1</td><td>FDRC0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td></tr></table>

The FDRC bits specify the 16-bit fault detect recovery time delay. When FAULT is asserted, the TRISTATE output is immediately asserted low and held low for the time period specified by this constant. A constant value of  $0 \times 0001$  in this register is approximately  $0.083 \mathrm{~ms}$ . The default value of  $0 \times 000C$  gives approximately  $0.1 \mathrm{~ms}$ .

# 8.16 Device status register (addr 0x2D)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>PLLUL</td><td>FAULT</td><td>UVFAULT</td><td>OVFAULT</td><td>OCFAULT</td><td>OCWARN</td><td>TFAULT</td><td>TWARN</td></tr></table>

This read-only register provides fault and thermal-warning status information from the power control block. Logic value 1 for faults or warning means normal state. Logic 0 means a fault or warning detected on power bridge. The PLLUL = 1 means that the PLL is not locked.

Table 72. Status register bits  

<table><tr><td>Bit</td><td>R/W</td><td>RST</td><td>Name</td><td>Description</td></tr><tr><td>7</td><td>R</td><td>-</td><td>PLLUL</td><td>0: PLL locked1: PLL not locked</td></tr><tr><td>6</td><td>R</td><td>-</td><td>FAULT</td><td>0: fault detected on power bridge1: normal operation</td></tr><tr><td>5</td><td>R</td><td>-</td><td>UVFAULT</td><td>0: VCCxX internally detected&lt; undervoltage threshold</td></tr><tr><td>4</td><td>R</td><td>-</td><td>OVFAULT</td><td>0: VCCxX internally detected&gt; overvoltage threshold</td></tr><tr><td>3</td><td>R</td><td>-</td><td>OCFAULT</td><td>0: overcurrent fault detected</td></tr><tr><td>2</td><td>R</td><td>-</td><td>OCWARN</td><td>0: overcurrent warning</td></tr><tr><td>1</td><td>R</td><td>-</td><td>TFAULT</td><td>0: thermal fault, junction temperature over limit detection</td></tr><tr><td>0</td><td>R</td><td>-</td><td>TWARN</td><td>0: thermal warning, junction temperature is close to the fault condition</td></tr></table>

# 8.17 EQ coefficients and DRC configuration register (addr 0x31)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>XOB</td><td>Reserved</td><td>Reserved</td><td>AMGC[3]</td><td>AMGC[2]</td><td>Reserved</td><td>SEL[1]</td><td>SEL[0]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

Table 73. EQ RAM select  

<table><tr><td>SEL[1:0]</td><td>EQ RAM bank selected</td></tr><tr><td>00/11</td><td>Bank 0 activated</td></tr><tr><td>01</td><td>Bank 1 activated</td></tr><tr><td>10</td><td>Bank 2 activated</td></tr></table>

Bits AMGC[3:2] change the behavior of the bits AMGC[1:0] as given in Table 74 below.

Table 74. Anti-clipping and DRC preset  

<table><tr><td>AMGC[3:2]</td><td>Anti clipping and DRC preset selected</td></tr><tr><td>00</td><td>DRC/Anti-clipping behavior described in Table 54 on page 57 (default).</td></tr><tr><td>01</td><td>DRC/Anti-clipping behavior is described Table 75 on page 75</td></tr><tr><td>10/11</td><td>Reserved, do not use</td></tr></table>

When AMGC[3:2] = 01 then the bits 1:0 are defined as given here in Table 75.

Table 75. Anti-clipping selection for AMGC[3:2] = 01  

<table><tr><td>AMGC[1:0]</td><td>Mode</td></tr><tr><td>00</td><td>AC0, stereo anticlipping 0 dB limiter</td></tr><tr><td>01</td><td>AC1, stereo anticlipping +1.25 dB limiter</td></tr><tr><td>10</td><td>AC2, stereo anticlipping +2 dB limiter</td></tr><tr><td>11</td><td>Reserved do not use</td></tr></table>

The AC0, AC1, AC2 settings are designed for the loudspeaker protection function, limiting at the minimum any audio artifacts introduced by typical anti-clipping/DRC algorithms. More detailed information is available in the applications notes "Configurable output power rate using STA335BW" and "STA335BWS vs STA335BW".

The XOB bit can be used to bypass the crossover filters. Logic 1 means that the function is not active. In this case, the high-pass crossover filter works as a pass-through on the data path ( $b0 = 1$ , all the other coefficients at logic 0) while the low-pass filter is configured to have zero signal on channel-3 data processing (all the coefficients are at logic 0).

# 8.18 Extended configuration register (addr 0x36)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>Mdrc[1]</td><td>Mdrc[0]</td><td>PS48DB</td><td>XAR1</td><td>XAR2</td><td>BQ5</td><td>BQ6</td><td>BQ7</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

The extended configuration register provides access to  $\mathsf{B}^2\mathsf{DRC}$  and biquad 5, 6 and 7.

# 8.18.1 Dual-band DRC

The STA350Bx device provides a dual-band DRC ( $B^2DRC$ ) on the left and right channels data path, as depicted in Figure 32. Dual-band DRC is activated by setting MDRC[1:0] = 1x.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/5bc90556247310003b2db7e17960dbd188bd0192a12f02a62b18f93e605badb9.jpg)  
Figure 32.  $\mathsf{B}^2\mathsf{DRC}$  scheme

The low frequency information (LFE) is extracted from left and right channels, removing the high frequencies using a programmable biquad filter, and then computing the difference with the original signal. Limiter 1 (DRC1) is then used to control left/right high-frequency amplitude of the components, while limiter 2 (DRC2) is used to control the low-frequency components (see Chapter 8.11).

The cutoff frequency of the high-pass filters can be user-defined,  $\mathrm{XO}[3:0] = 0$ , or selected from the pre-defined values.

DRC1 and DRC2 are then used to independently limit L/R high frequencies and LFE channels amplitude (see Chapter 8.11) as well as their volume control. To be noted that, in this configuration, the dedicated channel 3 volume control can actually act as a bass boost enhancer as well (0.5 dB/step resolution).

The processed LFE channel is then recombined with the L and R channels in order to reconstruct the 2.0 output signal.

# Sub-band decomposition

The sub-band decomposition for  $\mathsf{B}^2\mathsf{DRC}$  can be configured specifying the cutoff frequency. The cutoff frequency can be programmed in two ways, using XO bits in register 0x0C, or using the "user programmable" mode (coefficients stored in RAM addresses 0x28 to 0x31).

For the user programmable mode, use the formulas below to compute the high-pass filters:

$$
b 0 = (1 + \text {a l p h a}) / 2 \quad a 0 = 1
$$

$$
b 1 = - (1 + a l p h a) / 2 \quad a 1 = - a l p h a
$$

$$
b 2 = 0 \quad a 2 = 0
$$

where  $\alpha = (1 - \sin (\omega_0)) / \cos (\omega_0)$  and  $\omega_0$  is the cutoff frequency.

A first-order filter is suggested to guarantee that for every  $\omega_0$  the corresponding low-pass filter obtained as the difference (as shown in Figure 32) will have a symmetric (relative to HP filter) frequency response, and the corresponding recombination after the DRC has low ripple. Second-order filters can be used as well, but in this case the filter shape must be carefully chosen to provide good low-pass response and minimum ripple recombination. For second-order filters it is not possible to give a closed formula to get the best coefficients, but empirical adjustment should be done.

# DRC settings

The DRC blocks used by  $\mathsf{B}^2\mathsf{DRC}$  are the same as those described in Chapter 8.11.  $\mathsf{B}^2\mathsf{DRC}$  configure automatically the DRC blocks in anticlipping mode. Attack and release thresholds can be selected using registers  $0\mathrm{x}32$ $0\mathrm{x}33$ $0\mathrm{x}34$ $0\mathrm{x}35$  , while attack and release rates are configured by registers  $0\mathrm{x}12$  and  $0\mathrm{x}14$

# Band down-mixing

The low-frequency band is down-mixed to the left and right channels at the  $\mathsf{B}^2\mathsf{DRC}$  output. Channel volume can be used to weight the bands recombination to fine-tune the overall frequency response.

# 8.18.2 EQ DRC mode

Setting MDRC = 01, it is possible to add a programmable biquad (the XO biquad at RAM addresses 0x28 to 0x2C is used for this purpose) to the Limiter/compressor measure path (side chain). Using EQDRC the peak detector input can be shaped in frequency using the programmable biquad. For example if a +2 dB bass boost is applied (using a low shelf filter for example), the effect is that the EQDRC output will limit bass frequencies to -2 dB below the selected attack threshold.

Generally speaking, if the biquad boosts frequency  $f$  with an amount of  $X$  dB, the level of a compressed sine wave at the output will be  $TH - X$ , where  $TH$  is the selected attack threshold.

Note: EQDRC works only if the biquad frequency response magnitude is  $\geq 0$  dB for every frequency.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/9882013853167f871a0a5eabadc9405b1f2fd8aa3c45d04abbcf85b7a068d7ce.jpg)  
Figure 33. EQDRC scheme

# 8.18.3 Extended post-scale range

<table><tr><td>PS48DB</td><td>Mode</td></tr><tr><td>0</td><td>Post-scale value is applied as defined in coefficient RAM</td></tr><tr><td>1</td><td>Post-scale value is applied with +48 dB offset with respect to the coefficient RAM value</td></tr></table>

Post-scale is an attenuation by default. When PS48DB is set to 1, a 48-dB offset is applied to the coefficient RAM value, so post-scale can act as a gain too.

# 8.18.4 Extended attack rate

The attack rate shown in Table 65 can be extended to provide up to an 8 dB/ms attack rate on both limiters.

<table><tr><td>XAR1</td><td>Mode</td></tr><tr><td>0</td><td>Limiter1 attack rate is configured using Table 65</td></tr><tr><td>1</td><td>Limiter1 attack rate is 8 dB/ms</td></tr></table>

<table><tr><td>XAR2</td><td>Mode</td></tr><tr><td>0</td><td>Limiter2 attack rate is configured using Table 65</td></tr><tr><td>1</td><td>Limiter2 attack rate is 8 dB/ms</td></tr></table>

# 8.18.5 Extended biquad selector

De-emphasis filter as well as bass and treble controls can be configured as user-defined filters when the equalization coefficients link is activated (BQL = 1) and the corresponding BQx bit is set to 1.

<table><tr><td>BQ5</td><td>Mode</td></tr><tr><td>0</td><td>Pre-set de-emphasis filter selected</td></tr><tr><td>1</td><td>User-defined biquad 5 coefficients are selected</td></tr></table>

<table><tr><td>BQ6</td><td>Mode</td></tr><tr><td>0</td><td>Pre-set bass filter selected as per Table 64</td></tr><tr><td>1</td><td>User-defined biquad 6 coefficients are selected</td></tr></table>

<table><tr><td>BQ7</td><td>Mode</td></tr><tr><td>0</td><td>Pre-set treble filter selected as per Table 64</td></tr><tr><td>1</td><td>User-defined biquad 7 coefficients are selected</td></tr></table>

When filters from 5th to 7th are configured as user-programmable, the corresponding coefficients are stored respectively in addresses 0x20-0x24 (BQ5), 0x25-0x29 (BQ6), 0x2A-0x2E (BQ7) as in Table 71.

Note: BQx bits are ignored if  $BQL = 0$  or if  $DEMP = 1$  (relevant for BQ5) or  $CxTCB = 1$  (relevant for BQ6 and BQ7).

# 8.19 EQ soft-volume configuration registers (addr 0x37 - 0x38)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td></td><td></td><td>SVUPE</td><td>SVUP[4]</td><td>SVUP[3]</td><td>SVUP[2]</td><td>SVUP[1]</td><td>SVUP[0]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td></td><td></td><td>SVDWE</td><td>SVDW4]</td><td>SVDW[3]</td><td>SVDW[2]</td><td>SVDW[1]</td><td>SVDW[0]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

The soft-volume update has a fixed rate by default. Using register 0x37 and 0x38 it is possible to override the default behavior allowing different volume change rates.

It is also possible to independently define the fade-in (volume is increased) and fade-out (volume is decreased) rates according to the desired behavior.

<table><tr><td>SVUPE</td><td>Mode</td></tr><tr><td>0</td><td>When volume is increased, use the default rate</td></tr><tr><td>1</td><td>When volume is increased, use the rates defined by SVUP[4:0]</td></tr></table>

When SVUPE = 1 the fade-in rate is defined by the SVUP[4:0] bits according to the following formula:

Fade-in rate  $= 48 / (N + 1)$  dB/ms

where  $N$  is the SVUP[4:0] value.

<table><tr><td>SVDWE</td><td>Mode</td></tr><tr><td>0</td><td>When volume is decreased, use the default rate</td></tr><tr><td>1</td><td>When volume is decreased, use the rates defined by SVDW[4:0]</td></tr></table>

When SVDWE = 1 the fade-out rate is defined by the SVDW[4:0] bits according to the following formula:

Fade-in rate  $= 48 / (N + 1)$  dB/ms

where  $N$  is the SVDW[4:0] value.

Note: For fade-out rates greater than 6 dB/msec it is suggested to disable the CPWMEN bit (Section 8.24.4) and ZCE bit (Section 8.5.7) in order to avoid any audible pop noise.

# 8.20 DRC RMS filter coefficients (addr 0x39-0x3E)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>R_C0[23]</td><td>R_C0[22]</td><td>R_C0[21]</td><td>R_C0[20]</td><td>R_C0[19]</td><td>R_C0[18]</td><td>R_C0[17]</td><td>R_C0[16]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>R_C0[15]</td><td>R_C0[14]</td><td>R_C0[13]</td><td>R_C0[12]</td><td>R_C0[11]</td><td>R_C0[10]</td><td>R_C0[9]</td><td>R_C0[8]</td></tr><tr><td>1</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>R_C0[7]</td><td>R_C0[6]</td><td>R_C0[5]</td><td>R_C0[4]</td><td>R_C0[3]</td><td>R_C0[2]</td><td>R_C0[1]</td><td>R_C0[0]</td></tr><tr><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>R_C1[23]</td><td>R_C1[22]</td><td>R_C1[21]</td><td>R_C1[20]</td><td>R_C1[19]</td><td>R_C1[18]</td><td>R_C1[17]</td><td>R_C1[16]</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>R_C1[15]</td><td>R_C1[14]</td><td>R_C1[13]</td><td>R_C1[12]</td><td>R_C1[11]</td><td>R_C1[10]</td><td>R_C1[9]</td><td>R_C1[8]</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>R_C1[7]</td><td>R_C1[6]</td><td>R_C1[5]</td><td>R_C1[4]</td><td>R_C1[3]</td><td>R_C1[2]</td><td>R_C1[1]</td><td>R_C1[0]</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td></tr></table>

Signal level detection in DRC algorithm is computed using the following formula:

$$
y (t) = c 0 ^ {*} \operatorname {a b s} (x (t)) + c 1 ^ {*} y (t - 1)
$$

where  $x(t)$  represents the audio signal applied to the limiter, and  $y(t)$  the measured level.

# 8.21 Extra volume resolution configuration registers (address 0x3F)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>VRESEN</td><td>VRESTG</td><td>C3VR[1]</td><td>C3VR[0]</td><td>C2VR[1]</td><td>C2VR[0]</td><td>C1VR[1]</td><td>C1VR[0]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

The extra volume resolution allows fine volume tuning by steps of 0.125dB.

The feature is enabled when VRESEN=1, as depicted in Figure 34. The overall channel volume in this case will be CxVol+CxVR (in dB). On top of the total volume range from -80 dB to +48 dB, this extra volume resolution works in a volume range from -80 dB to +42 dB. For volumes greater than +42 dB, this function must not be selected.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/397e3e49c1902ab9bb38a417b804c796df141e170615c27607303fd7c4dc5ec9.jpg)  
Figure 34. Extra resolution volume scheme

If VRESEN = 0 the channel volume is defined only by the CxVol registers.

Fine-tuning steps can be set according to the following table for channels 1, 2, 3:

<table><tr><td>CxVR</td><td>Mode</td></tr><tr><td>00</td><td>0 dB</td></tr><tr><td>01</td><td>-0.125 dB</td></tr><tr><td>10</td><td>-0.25 dB</td></tr><tr><td>11</td><td>-0.375 dB</td></tr></table>

Two different behaviors can be configured by the VRESTG bit:

- If VRESTG='0' the CxVR contribution is applied immediately after the corresponding I²C bits are written.  
- If VRESTG='1' the CxVR bits are effective on channel volume only after the corresponding CxVol register or master volume register is written (even to the previous values).

<table><tr><td>VRESEN</td><td>VRESTG</td><td>Mode</td></tr><tr><td>0</td><td>0</td><td>Extra volume resolution disabled</td></tr><tr><td>0</td><td>1</td><td>Extra volume resolution disabled</td></tr><tr><td>1</td><td>0</td><td>Volume fine-tuning enabled and applied immediately</td></tr><tr><td>1</td><td>1</td><td>Volume fine-tuning enabled and applied when master or channel volume is updated</td></tr></table>

# 8.22 Quantization error noise correction (address 0x48)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>NSHXEN</td><td>NSHB7EN</td><td>NSHB6EN</td><td>NSHB5EN</td><td>NSHB4EN</td><td>NSHB3EN</td><td>NSHB2EN</td><td>NSHB1EN</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

A special feature inside the digital processing block is available. In case of poles positioned at very low frequencies, biquad filters can generate some audible quantization noise or unwanted DC level. In order to avoid this kind of effect, a quantization noise-shaping capability can be used. The filter structure including this special feature, relative to each biquad, is shown in Figure 35.

By default, this capability is not activated to maintain backward compatibility with all the previous Sound Terminal products. The new feature can be enabled independently for each biquad using the I²C registers. The D7 bit, when set, is responsible for activating this function on the crossover filter while the other bits address any specific biquads according to the previous table. Channels 1 and 2 share the same settings. Bit D7 is effective also for channel 3 if the relative OCFG is used.

Figure 35. Biquad filter structure with quantization error noise-shaping  
![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/a169562121379be33179560bad0b36fa4d5aa16f19ac4998b9979893537af2f7.jpg)  
AM045197v1

8.23 Extended coefficient range up to -4...4 (address 0x49, 0x4A)  

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>CXTB4[1]</td><td>CXTB4[0]</td><td>CXTB3[1]</td><td>CXTB3[0]</td><td>CX_B2[1]</td><td>CXTB2[0]</td><td>CXTB1[1]</td><td>CXTB1[0]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>Reserved</td><td>Reserved</td><td>CXTB7[1]</td><td>CXTB7[0]</td><td>CXTB6[1]</td><td>CXTB6[0]</td><td>CXTB5[1]</td><td>CXTB5[0]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

Biquads from 1 to 7 have in the STA350Bx the possibility to extend the coefficient range from [-1,1) to [-4..4). This allows the realization of high shelf filters that may require a coefficients dynamic greater in absolute value than 1.

Three ranges are available, [-1;1) [-2;2) [-4;4). By default the extended range is not activated to maintain backward compatibility with all the previous Sound Terminal products.

Each biquad has its independent setting according to the following table:

Table 76. Biquad filter settings  

<table><tr><td>CEXT_Bx[1]</td><td>CEXT_Bx[0]</td><td></td></tr><tr><td>0</td><td>0</td><td>[-1;1)</td></tr><tr><td>0</td><td>1</td><td>[-2;2)</td></tr><tr><td>1</td><td>0</td><td>[-4;4)</td></tr><tr><td>1</td><td>1</td><td>Reserved</td></tr></table>

In this case the user can decide, for each filter stage, the right coefficients range. Note that for a given biquad the same range will be applied to Left and Right (Channel 1 and Channel 2).

The crossover biquad does not have the availability of this feature, maintaining the [-1;1) range unchanged.

# 8.24 Miscellaneous registers (address 0x4B, 0x4C)

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>RPDNEN</td><td>NSHHPEN</td><td>BRIDGOFF</td><td>Reserved</td><td>Reserved</td><td>CPWMEN</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr><tr><td>Reserved</td><td>Reserved</td><td>Reserved</td><td>PNDLSL[2]</td><td>PNDLSL[1]</td><td>PNDLSL[0]</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

# 8.24.1 Rate powerdown enable (RPDNEN) bit (address 0x4B, bit D7)

In the STA350Bx, by default, the power-down pin and  $\mathrm{I}^2\mathrm{C}$  power-down act on mute commands to perform the fadeout. This default can be changed so that the fadeout can be started using the master volume. The RPDNEN bit, when set, activates this feature.

# 8.24.2 Noise-shaping on DC cut filter enable (NSHHPEN) bit (address 0x4B, bit D6)

Following the description in Section 8.22, this bit, when set, enables the noise-shaping technique on the DC cutoff filter. Channels 1 and 2 share the same settings.

# 8.24.3 Bridge immediate off (BRIDGOFF) bit (address 0x4B, bit D5)

A fadeout procedure is started in the STA350Bx once the PWDN function is enabled. Independently from the fadeout time, after 13 million clock cycles (PLL internal frequency) the bridge is put in powerdown (tri-state mode). There is also the possibility to change this behavior so that the power bridge will be switched off immediately after the PWDN pin is tied to ground, without therefore waiting for the 13 million clock cycles. The BRIDGOFF bit, when set, activates this function. Obviously the immediate power-down will generate a pop noise at the output. Therefore this procedure must be used only in case pop noise is not relevant in the application. Note that this feature works only for hardware PWDN assertion and not for a powerdown applied through the I²C interface. Refer to Section 8.24.5 in order to program a different number of clock cycles.

# 8.24.4 Channel PWM enable (CPWMEN) bit (address 0x4B, bit D2)

This bit, when set, activates a mute output in case the volume will reach a value lower than -76 dBFS.

# 8.24.5 Power-down delay selector (PNDLSL[2:0]) bits (address 0x4C, bit D4, D3, D2)

As per Section 8.24.3, the assertion of PWDN activates a counter that, by default, after 13 million clock cycles puts the power bridge in tri-state mode, independently from the fadeout time. Using these registers it is possible to program this counter according to the following table:

<table><tr><td>PNDLSL[2]</td><td>PNDLSL[1]</td><td>PNDLSL[2]</td><td>Fade out time</td></tr><tr><td>0</td><td>0</td><td>0</td><td>Default time (13 M clock cycles)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>Default time divided by 2</td></tr><tr><td>0</td><td>1</td><td>0</td><td>Default time divided by 4</td></tr><tr><td>0</td><td>1</td><td>1</td><td>Default time divided by 8</td></tr><tr><td>1</td><td>0</td><td>0</td><td>Default time divided by 16</td></tr><tr><td>1</td><td>0</td><td>1</td><td>Default time divided by 32</td></tr><tr><td>1</td><td>1</td><td>0</td><td>Default time divided by 64</td></tr><tr><td>1</td><td>1</td><td>1</td><td>Default time divided by 128</td></tr></table>

# 9 PowerSSO-36 slug-down package thermal characteristics (STA350BW)

Using a four-layer PCB the thermal resistance junction-to-ambient with 2 copper ground areas of  $6 \times 4 \, \text{cm}^2$  and with 24 via holes (see Figure 36) is  $17^{\circ}\text{C/W}$  in natural air convection.

The dissipated power within the device depends primarily on the supply voltage, load impedance and output modulation level.

Thus, the maximum estimated dissipated power for the STA350BW is:

$2 \times 40 \mathrm{~W} @ 8 \Omega, 25.5 \mathrm{~V}$

Pd max  $\sim 8$  W

$2 \times 17 \mathrm{~W} + 1 \times 35 \mathrm{~W} @ 4 \Omega, 8 \Omega, 25 \mathrm{~V}$

Pd max  $< 7$  W

Figure 36. Double-layer PCB with 2 copper ground areas and 24 via holes  
![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/d02b767887389bad106450769ed30662e7dd6f25a5b9fb9cfc1a1ddc5ecec15e.jpg)  
AM045200v1  
Figure 37 shows the power derating curve for the PowerSSO-36 slug-down package on PCBs with copper areas of  $5 \times 4 \, \text{cm}^2$  and  $6 \times 4 \, \text{cm}^2$ .

Figure 37. PowerSSO-36 power derating curve  
![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/f4fe990f90533d65c2eb14622e36bf8cceaa7b0f8bf2cd2cf4277c15e51c104a.jpg)  
AM045201v1

# 10 Package information

In order to meet environmental requirements, ST offers these devices in different grades of ECOPACK packages, depending on their level of environmental compliance. ECOPACK specifications, grade definitions and product status are available at: www.st.com. ECOPACK is an ST trademark.

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/4c71f58dd27675b242cf9954111c515c7982f7944b5f1028a255492fa113c2d3.jpg)  
Figure 38. PowerSSO-36 EPD package outline

Table 77. PowerSSO-36 EPD mechanical data  

<table><tr><td rowspan="2">Symbol</td><td colspan="3">Dimensions in mm</td><td colspan="3">Dimensions in inches</td></tr><tr><td>Min.</td><td>Typ.</td><td>Max.</td><td>Min.</td><td>Typ.</td><td>Max.</td></tr><tr><td>A</td><td>2.15</td><td>-</td><td>2.47</td><td>0.085</td><td>-</td><td>0.097</td></tr><tr><td>A2</td><td>2.15</td><td>-</td><td>2.40</td><td>0.085</td><td>-</td><td>0.094</td></tr><tr><td>a1</td><td>0.00</td><td>-</td><td>0.10</td><td>0.00</td><td>-</td><td>0.004</td></tr><tr><td>b</td><td>0.18</td><td>-</td><td>0.36</td><td>0.007</td><td>-</td><td>0.014</td></tr><tr><td>c</td><td>0.23</td><td>-</td><td>0.32</td><td>0.009</td><td>-</td><td>0.013</td></tr><tr><td>D</td><td>10.10</td><td>-</td><td>10.50</td><td>0.398</td><td>-</td><td>0.413</td></tr><tr><td>E</td><td>7.40</td><td>-</td><td>7.60</td><td>0.291</td><td>-</td><td>0.299</td></tr><tr><td>e</td><td>-</td><td>0.5</td><td>-</td><td>-</td><td>0.020</td><td>-</td></tr><tr><td>e3</td><td>-</td><td>8.5</td><td>-</td><td>-</td><td>0.335</td><td>-</td></tr><tr><td>F</td><td>-</td><td>2.3</td><td>-</td><td>-</td><td>0.091</td><td>-</td></tr><tr><td>G</td><td>-</td><td>-</td><td>0.10</td><td>-</td><td>-</td><td>0.004</td></tr><tr><td>H</td><td>10.10</td><td>-</td><td>10.50</td><td>0.398</td><td>-</td><td>0.413</td></tr><tr><td>h</td><td>-</td><td>-</td><td>0.40</td><td>-</td><td>-</td><td>0.016</td></tr><tr><td>k</td><td>0</td><td>-</td><td>8 degrees</td><td>0</td><td>-</td><td>8 degrees</td></tr></table>

Table 77. PowerSSO-36 EPD mechanical data  

<table><tr><td rowspan="2">Symbol</td><td colspan="3">Dimensions in mm</td><td colspan="3">Dimensions in inches</td></tr><tr><td>Min.</td><td>Typ.</td><td>Max.</td><td>Min.</td><td>Typ.</td><td>Max.</td></tr><tr><td>L</td><td>0.60</td><td>-</td><td>1.00</td><td>0.024</td><td>-</td><td>0.039</td></tr><tr><td>M</td><td>-</td><td>4.30</td><td>-</td><td>-</td><td>0.169</td><td>-</td></tr><tr><td>N</td><td>-</td><td>-</td><td>10 degrees</td><td>-</td><td>-</td><td>10 degrees</td></tr><tr><td>O</td><td>-</td><td>1.20</td><td>-</td><td>-</td><td>0.047</td><td>-</td></tr><tr><td>Q</td><td>-</td><td>0.80</td><td>-</td><td>-</td><td>0.031</td><td>-</td></tr><tr><td>S</td><td>-</td><td>2.90</td><td>-</td><td>-</td><td>0.114</td><td>-</td></tr><tr><td>T</td><td>-</td><td>3.65</td><td>-</td><td>-</td><td>0.144</td><td>-</td></tr><tr><td>U</td><td>-</td><td>1.00</td><td>-</td><td>-</td><td>0.039</td><td>-</td></tr><tr><td>X</td><td>4.10</td><td>-</td><td>4.70</td><td>0.161</td><td>-</td><td>0.185</td></tr><tr><td>Y</td><td>6.50</td><td>-</td><td>7.10</td><td>0.256</td><td>-</td><td>0.280</td></tr></table>

![](https://cdn-mineru.openxlab.org.cn/result/2025-12-22/88d21d79-917e-4b56-82a8-8a96e23521a0/e1e5e280707544dbd2d32504651492917adac100b4732eabea7f2ac06cdb426f.jpg)  
Figure 39. PowerSSO36 (slug-up) package outline

Table 78. PowerSSO36 exposed pad up mechanical data  

<table><tr><td rowspan="2">Symbol</td><td colspan="3">Dimensions in mm</td><td colspan="3">Dimensions in inch</td></tr><tr><td>Min.</td><td>Typ.</td><td>Max.</td><td>Min.</td><td>Typ.</td><td>Max.</td></tr><tr><td>A</td><td>2.15</td><td>-</td><td>2.45</td><td>0.085</td><td>-</td><td>0.096</td></tr><tr><td>A2</td><td>2.15</td><td>-</td><td>2.35</td><td>0.085</td><td>-</td><td>0.092</td></tr><tr><td>a1</td><td>0</td><td>-</td><td>0.1</td><td>0.00</td><td>-</td><td>0.004</td></tr><tr><td>b</td><td>0.18</td><td>-</td><td>0.36</td><td>0.007</td><td>-</td><td>0.014</td></tr><tr><td>c</td><td>0.23</td><td>-</td><td>0.32</td><td>0.009</td><td>-</td><td>0.013</td></tr><tr><td>D</td><td>10.10</td><td>-</td><td>10.50</td><td>0.398</td><td>-</td><td>0.413</td></tr><tr><td>E</td><td>7.4</td><td>-</td><td>7.6</td><td>0.291</td><td>-</td><td>0.299</td></tr><tr><td>e</td><td>-</td><td>0.5</td><td>-</td><td>-</td><td>0.020</td><td>-</td></tr><tr><td>e3</td><td>-</td><td>8.5</td><td>-</td><td>-</td><td>0.335</td><td>-</td></tr><tr><td>F</td><td>-</td><td>2.3</td><td>-</td><td>-</td><td>0.091</td><td>-</td></tr><tr><td>G</td><td>-</td><td>-</td><td>0.1</td><td>-</td><td>-</td><td>0.004</td></tr><tr><td>H</td><td>10.1</td><td>-</td><td>10.5</td><td>-</td><td>-</td><td>0.413</td></tr><tr><td>h</td><td>-</td><td>-</td><td>0.4</td><td>-</td><td>-</td><td>0.016</td></tr><tr><td>k</td><td>0 deg</td><td>-</td><td>8 deg</td><td>0 deg</td><td>-</td><td>8 deg</td></tr></table>

Table 78. PowerSSO36 exposed pad up mechanical data (continued)  

<table><tr><td rowspan="2">Symbol</td><td colspan="3">Dimensions in mm</td><td colspan="3">Dimensions in inch</td></tr><tr><td>Min.</td><td>Typ.</td><td>Max.</td><td>Min.</td><td>Typ.</td><td>Max.</td></tr><tr><td>L</td><td>0.55</td><td>-</td><td>0.85</td><td>0.022</td><td></td><td>0.033</td></tr><tr><td>M</td><td>-</td><td>4.3</td><td>-</td><td>-</td><td>0.169</td><td>-</td></tr><tr><td>N</td><td>-</td><td>-</td><td>10 deg</td><td>-</td><td>-</td><td>10 deg</td></tr><tr><td>O</td><td>-</td><td>1.2</td><td>-</td><td>-</td><td>0.047</td><td>-</td></tr><tr><td>Q</td><td>-</td><td>0.8</td><td>-</td><td>-</td><td>0.031</td><td>-</td></tr><tr><td>S</td><td>-</td><td>2.9</td><td>-</td><td>-</td><td>0.114</td><td>-</td></tr><tr><td>T</td><td>-</td><td>3.65</td><td>-</td><td>-</td><td>0.114</td><td>-</td></tr><tr><td>U</td><td>-</td><td>1.0</td><td>-</td><td>-</td><td>0.039</td><td>-</td></tr></table>

# 11 Ordering information

Table 79. Order code  

<table><tr><td>Order code</td><td>Temperature range °C</td><td>Package</td><td>Packing</td></tr><tr><td>STA350BTR</td><td>-20 to 85</td><td>PowerSSO36 (slug-up)</td><td rowspan="2">Tape and reel</td></tr><tr><td>STA350BWTR</td><td>-20 to 85</td><td>PowerSSO-36 (slug-down)</td></tr></table>

# 12 Revision history

Table 80. Document revision history  

<table><tr><td>Date</td><td>Revision</td><td>Changes</td></tr><tr><td>11-Mar-2011</td><td>1</td><td>Initial release.</td></tr><tr><td>20-Apr-2011</td><td>2</td><td>Updated Figure 4: Demonstration board, 2.0 channels
Added Figure 5: Mono parallel BTL schematic</td></tr><tr><td>13-Apr-2012</td><td>3</td><td>Updated min. and typ. values for Isc in Table 6: Electrical specifications - power section</td></tr><tr><td>20-Sep-2013</td><td>4</td><td>Added Section 5 on page 25
Modified Note:: The read write operation on RAM coefficients works only if RLCKI (pin29) is switching and stable (ref. Table 7, tLRJT timing) and PLL must be locked (ref bit D7 reg 0x2D).
Updated Company information appearing on last page of document</td></tr><tr><td>18-Jul-2017</td><td>5</td><td>Added STA350B device, related package information and Section 11: Ordering information. Minor changes throughout the document.</td></tr><tr><td>11-Apr-2018</td><td>6</td><td>Added Section 3.6: Power-on/off sequence.
Minor text changes throughout the document.</td></tr><tr><td>07-Jun-2019</td><td>7</td><td>Updated cover image and Figure 2.</td></tr></table>

# IMPORTANT NOTICE - PLEASE READ CAREFULLY

STMicroelectronics NV and its subsidiaries ("ST") reserve the right to make changes, corrections, enhancements, modifications, and improvements to ST products and/or to this document at any time without notice. Purchasers should obtain the latest relevant information on ST products before placing orders. ST products are sold pursuant to ST's terms and conditions of sale in place at the time of order acknowledgement.

Purchasers are solely responsible for the choice, selection, and use of ST products and ST assumes no liability for application assistance or the design of Purchasers' products.

No license, express or implied, to any intellectual property right is granted by ST herein.

Resale of ST products with provisions different from the information set forth herein shall void any warranty granted by ST for such product.

ST and the ST logo are trademarks of ST. For additional information about ST trademarks, please refer to www.st.com/trademarks. All other product or service names are the property of their respective owners.

Information in this document supersedes and replaces information previously supplied in any prior versions of this document.

© 2019 STMicroelectronics – All rights reserved