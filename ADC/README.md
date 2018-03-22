
# Initialization and Configuration

In order for the **ADC** module to be used, the PLL must be enabled and programmed to a supported crystal frequency in the RCC register (see page 254). Using unsupported frequencies can cause faulty operation in the ADC module.

## Module Initialization

Initialization of the **ADC** module is a simple process with very few steps: enabling the clock to the **ADC**, disabling the analog isolation circuit associated with all inputs that are to be used, and reconfiguring the sample sequencer priorities(if needed).
The initialization sequence for the **ADC** is as follows:

1. Enable the **ADC** clock using **RCGCADC** register [(see page 325)](http://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf).
![RCGCADC](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/RCGCADC.png)
2. Enable the clock to the appropriate **GPIO** modules via the **RCGCGPIO** register [(see page 340)](http://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf). To find out which GPIO ports to enable, refer to “Signal Description” on page 801.
![RCGCGPIO_1](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/RCGCGPIO_1.png)
![RCGCGPIO_2](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/RCGCGPIO_2.png)
3. Set the **GPIO AFSEL** bits for the **ADC** input pins (see page 671). To determine which GPIOs to configure, see Table 23-4 on page 1344.
![GPIOAFSEL](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/GPIOAFSEL.png)
4. Configure the **AINx** signals to be analog inputs by clearing the corresponding **DEN** bit in the **GPIO** Digital Enable **(GPIODEN)** register (see page 682).
![GPIODEN](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/GPIODEN.png)
5. Disable the analog isolation circuit for all **ADC** input pins that are to be used by
writing a 1 to the appropriate bits of the **GPIOAMSEL** register (see page 687) in the
associated GPIO block.
![GPIOAMSEL](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/GPIOAMSEL.png)
6. If required by the application, reconfigure the sample sequencer priorities in the
**ADCSSPRI** register. The default configuration has Sample Sequencer 0 with the
highest priority and Sample Sequencer 3 as the lowest priority.
![ADCSSPRI_1](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/ADCSSPRI_1.png)
![ADCSSPRI_2](https://github.com/TivaCollection/TivaLibraries/blob/master/ADC/resources/images/Module%20Initialization/ADCSSPRI_2.png)
## Sample Sequencer Configuration

Configuration of the sample sequencers is slightly more complex than the module
initialization because each sample sequencer is completely programmable.
The configuration for each sample sequencer should be as follows:

1. Ensure that the sample sequencer is disabled by clearing the corresponding **ASENn** bit in the **ADCACTSS** register. Programming of the sample sequencers is allowed without having them enabled. Disabling the sequencer during programming
prevents erroneous execution if a trigger event were to occur during the configuration process.
2. Configure the trigger event for the sample sequencer in the **ADCEMUX** register.
3. When using a **PWM** generator as the trigger source, use the **ADC** Trigger Source Select **(ADCTSSEL)** register to specify in which **PWM** module the generator is located. The default register reset selects **PWM** module 0 for all generators.
4. For each sample in the sample sequence, configure the corresponding input source
in the **ADCSSMUXn** register.
5. For each sample in the sample sequence, configure the sample control bits in the
corresponding nibble in the **ADCSSCTLn** register. When programming the last
nibble, ensure that the END bit is set. Failure to set the END bit causes
unpredictable behavior.
6. If interrupts are to be used, set the corresponding **MASK** bit in the **ADCIM** register.
7. Enable the sample sequencer logic by setting the corresponding **ASENn** bit in the **ADCACTSS** register.
