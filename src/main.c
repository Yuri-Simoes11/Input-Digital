#include <zephyr/kernel.h>            // Funções básicas do Zephyr (ex: k_msleep, k_thread, etc.)
#include <zephyr/device.h>            // API para obter e utilizar dispositivos do sistema
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>      // API para controle de pinos de entrada/saída (GPIO)

#define PORTB_NODE DT_NODELABEL(gpiob)
#define INPUT_PORT  "gpio@400ff0c0"   // Porta D configurada com endereço direto
                                      // Pegue o endereço no zephyr.dts dentro de pio \ build
#define INPUT_PIN7   7                // PTD7
#define INPUT_PIN6   6                // PTD6

void main(void) {

    const struct device *input_dev;
    int ret7, ret6, val7, val6;

    const struct device *portd = DEVICE_DT_GET(DT_NODELABEL(gpiod));

    input_dev = device_get_binding(INPUT_PORT);
    if (!input_dev) {
        printk("Erro ao acessar porta %s\n", INPUT_PORT);
        return;
    }

    ret7 = gpio_pin_configure(input_dev, INPUT_PIN7, GPIO_INPUT);
    if (ret7 != 0) {
        printk("Erro ao configurar pino %d\n", INPUT_PIN7);
        return;
    }
    ret7 = gpio_pin_configure(input_dev, INPUT_PIN7, GPIO_INPUT | GPIO_PULL_UP);

    ret6 = gpio_pin_configure(input_dev, INPUT_PIN6, GPIO_INPUT);
    if (ret6 != 0) {
        printk("Erro ao configurar pino %d\n", INPUT_PIN6);
        return;
    }
    ret6 = gpio_pin_configure(input_dev, INPUT_PIN6, GPIO_INPUT | GPIO_PULL_UP);

    while (1) {
        val7 = gpio_pin_get(input_dev, INPUT_PIN7);
        val6 = gpio_pin_get(input_dev, INPUT_PIN6); 
        printk("Valor do PTD7: %d\n", val7);
        printk("Valor do PTD6: %d\n", val6);
        k_msleep(500);
    }
}