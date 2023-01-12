/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define LIS3DH_G_CHIP_ADDR (0x18 << 1)		// G
//#define LIS3DH_V_CHIP_ADDR (0x19 << 1)		// V
//#define LIS3DH_WHO_AM_I	0x0f				// Address of the registers
//#define LIS3DH_OUT_X_L 0x28				// output address
//#define LIS3DH_CTRL_REG1 0x20
//#define LIS3DH_CTRL_REG4 0x23
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
//uint8_t buf[32];
////int16_t x = 0;      // set value = starting point
////int16_t y = 0;
////int16_t z = 0;
//HAL_StatusTypeDef ret;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t buf[32];
uint8_t x = 0;
uint8_t y = 0;
uint8_t z = 0;
#define LIS3DH_WHO_AM_I			0x0f
#define LIS3DH_G_CHIP_ADDR 		(0x18 << 1)
#define LIS3DH_V_CHIP_ADDR 		(0x19 << 1)

#define LIS3DH_STATUS_REG_AUX	0x07

#define LIS3DH_CTRL_REG1		0x20
#define LIS3DH_CTRL_REG2		0x21
#define LIS3DH_CTRL_REG3		0x22
#define LIS3DH_CTRL_REG4		0x23
#define LIS3DH_CTRL_REG5		0x24
#define LIS3DH_CTRL_REG6		0x25
#define LIS3DH_OUT_X_L			0x28
HAL_StatusTypeDef ret;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  buf[0] = LIS3DH_CTRL_REG1;
  buf[1] = 0x97;

  ret = HAL_I2C_Master_Transmit(&hi2c3, LIS3DH_V_CHIP_ADDR, buf, 2, HAL_MAX_DELAY);
  if (ret != HAL_OK){
  	 sprintf((char*)buf,"ErrorTx LIS3DH_CTRL_REG1\r\n");
     HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
  }

  buf[0] = LIS3DH_CTRL_REG4;
  buf[1] = 0x08;

  ret = HAL_I2C_Master_Transmit(&hi2c3, LIS3DH_V_CHIP_ADDR, buf, 2, HAL_MAX_DELAY);
  if (ret != HAL_OK){
  	 sprintf((char*)buf,"ErrorTx LIS3DH_CTRL_REG4\r\n");
  	 HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hic3, LIS3DH_V_CHIP_ADDR, buf, 3, 100 );
//	  if ( ret != HAL_OK ){
//	//		  sprintf((char*)buf, "ErrorRx WHO_AM_I");
//	  		  sprintf((char*)buf, "ErrorRx LIS3DH_OUT_X_L");
//	  		  HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
//	  }
//	  buf[0] = LIS3DH_OUT_X_L | 0x80;
	  buf[0] = LIS3DH_WHO_AM_I;
	  ret = HAL_I2C_Master_Transmit(&hi2c3, LIS3DH_V_CHIP_ADDR, buf, 1, HAL_MAX_DELAY);

	  if ( ret != HAL_OK ){
	//		  sprintf((char*)buf, "ErrorTx WHO_AM_I");
		  sprintf((char*)buf, "ErrorTx LIS3DH_OUT_X_L");
		  HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  }

	  ret = HAL_I2C_Master_Receive(&hi2c3, LIS3DH_V_CHIP_ADDR, buf, 1, HAL_MAX_DELAY);

	  if ( ret != HAL_OK ){
	//		  sprintf((char*)buf, "ErrorRx WHO_AM_I");
		  sprintf((char*)buf, "ErrorRx LIS3DH_OUT_X_L");
		  HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  }

	  sprintf((char*)buf, "ID: 0x%02X\r\n", buf[0]);
	  HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);

//	  int16_t x = buf[1] << 8 | buf[0];
//	  int16_t y = buf[3] << 8 | buf[2];
//	  int16_t z = buf[5] << 8 | buf[4];

//	  sprintf((char*)buf, "x:%d, y:%d, z:%d\r\n", x,y,z);
//	  HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);

     HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
