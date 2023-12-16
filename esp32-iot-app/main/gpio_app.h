#ifndef MAIN_GPIO_APP_H
#define MAIN_GPIO_APP_H

// output buz 19 +
// input read flame sensor
#define GPIO_APP_PIN_BUZ 19
#define GPIO_APP_PIN_FLAME 35

/**
 * Starts gpio_app task
 */
void gpio_app_task_start(void);

#endif