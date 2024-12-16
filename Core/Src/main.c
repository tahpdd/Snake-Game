
#include "main.h"

#include "ssd1306.h"
#include "snake.h"
#include "font.h"
I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);



void updateSnake(struct snake *s, int snakeLen) {
	for (int i = snakeLen - 1; i > 0; i--) {
    	s[i].x = s[i - 1].x;
    	s[i].y = s[i - 1].y;
	}
}

int checkColli(struct snake *s, int snakeLen, int x, int y) {
	for (int i = 1; i < snakeLen; i++) {
		int temp = s[0].x + x;
		if (temp == s[i].x && s[0].y + y == s[i].y) {
			return 1;
		}
	}
	return 0;
}

void end(int snakeLen){
	SSD1306_DrawFilledRectangle(51, 12, 26, 20, 0);
	SSD1306_DrawRectangle(51, 12, 26, 20, 1);
	int fn = snakeLen / 10;
	int sn = snakeLen % 10;

	outputResult(fn, sn, 54, 15);
	SSD1306_UpdateScreen();
	while (1) {}
}


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();

	SSD1306_Init();

	// Draw the playground
	SSD1306_DrawLine(124,0,124,63,1);   // right
	SSD1306_DrawLine(0,0,0,63,1);     // left
	SSD1306_DrawLine(0,61,127,61,1); // down
	SSD1306_DrawLine(0,0,127,0,1);  // up

	SSD1306_UpdateScreen();

	uint8_t count = 0;
	int snakeLen = 4;
	uint8_t delay = 150;

	struct snake s[100];

	// snake init
	for (int i = 0; i < snakeLen; i++) {
		s[i].x = (128/2) + 3*i;
		s[i].y = 62 / 2;
	}

	// output snake
	for (int i = 0; i < snakeLen; i++) {
		SSD1306_DrawRectangle(s[i].x, s[i].y, 2, 2, 1);
	}

	// output fruit
	uint8_t fruitX = 7;
	uint8_t fruitY = 4;
	SSD1306_DrawRectangle(fruitX, fruitY, 2, 2, 1);

	SSD1306_UpdateScreen();
	uint8_t l = 1;
	uint8_t r = 0;
	uint8_t u = 0;
	uint8_t d = 0;

	while (1) {
		// move left, s[0] = head
		if (l == 1) {
			while ( l == 1 ) {

				if (checkColli(s, snakeLen, -3, 0) == 1) {
					end( snakeLen);
					break;

				}
				if ( s[0].x == fruitX + 3 && s[0].y == fruitY) {
					snakeLen++;
					s[snakeLen - 1].x = s[snakeLen - 2].x + 3;
					s[snakeLen - 1].y = s[snakeLen - 2].y;

					NewFruit(s, snakeLen, &fruitX, &fruitY);
					SSD1306_UpdateScreen();
				}
				if ( s[0].x == 1) {
					uint8_t lastX = s[snakeLen - 1].x;
					uint8_t lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
					updateSnake(s, snakeLen);
					s[0].x = 121;
					s[0].y = s[0].y;

					lastX = s[snakeLen - 1].x;
					lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
				}
				else {
					uint8_t lastX = s[snakeLen - 1].x;
					uint8_t lastY = s[snakeLen - 1].y;
					updateSnake(s, snakeLen);
					s[0].x -= 3;


					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);

					SSD1306_UpdateScreen();
					HAL_Delay(delay);
				}
				// check up and down
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 1) {
					l = 0;
					d = 0;
					r = 0;
					u = 1;

					break;
				}
				else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 1) {
					l = 0;
					u = 0;
					r = 0;
					d = 1;

					break;
				}

			}
		}
		else if (u == 1) {
			// move up, s[0] = head
			while ( u == 1 ) {

				if (checkColli(s, snakeLen, 0, -3) == 1) {
					end( snakeLen);
					break;

				}
				if ( s[0].y == fruitY + 3 && s[0].x == fruitX) {
					snakeLen++;
					s[snakeLen - 1].x = s[snakeLen - 2].x;
					s[snakeLen - 1].y = s[snakeLen - 2].y + 3;

					NewFruit(s, snakeLen, &fruitX, &fruitY);
					SSD1306_UpdateScreen();
				}
				if ( s[0].y == 1 ) {
					uint8_t lastX = s[snakeLen - 1].x;
					uint8_t lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
					updateSnake(s, snakeLen);
					s[0].x = s[0].x;
					s[0].y = 58;

					lastX = s[snakeLen - 1].x;
					lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
				}
				else {
					int lastX = s[snakeLen - 1].x;
					int lastY = s[snakeLen - 1].y;
					updateSnake(s, snakeLen);

					s[0].y -= 3;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);

					SSD1306_UpdateScreen();
					count++;
					HAL_Delay(delay);
				}
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1) {
					d = 0;
					r = 0;
					u = 0;
					l = 1;
					break;
				}
				else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1) {
					d = 0;
					l = 0;
					u = 0;
					r = 1;
					break;
				}
			}
		}
		else if (d == 1) {
			// move up, s[0] = head
			while ( d == 1 ) {


				if ( s[0].y == fruitY - 3 && s[0].x == fruitX) {
					snakeLen++;
					s[snakeLen - 1].x = s[snakeLen - 2].x;
					s[snakeLen - 1].y = s[snakeLen - 2].y - 3;

					NewFruit(s, snakeLen, &fruitX, &fruitY);
					SSD1306_UpdateScreen();
				}
				if (checkColli(s, snakeLen, 0, 3) == 1) {
					end( snakeLen);
					break;

				}
				if ( s[0].y == 58 ) {
					uint8_t lastX = s[snakeLen - 1].x;
					uint8_t lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
					updateSnake(s, snakeLen);
					s[0].x = s[0].x;
					s[0].y = 1;

					lastX = s[snakeLen - 1].x;
					lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
				}
				else {
					int lastX = s[snakeLen - 1].x;
					int lastY = s[snakeLen - 1].y;
					updateSnake(s, snakeLen);

					s[0].y += 3;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);

					SSD1306_UpdateScreen();
					count++;
					HAL_Delay(delay);
				}
				// check left and right
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1) {
					d = 0;
					r = 0;
					u = 0;
					l = 1;
					break;
				}
				else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1) {
					d = 0;
					l = 0;
					u = 0;
					r = 1;
					break;
				}
			}
		}
		else if (r == 1) {
			while ( r == 1 ) {

				if ( s[0].x == fruitX - 3 && s[0].y == fruitY) {
					snakeLen++;
					s[snakeLen - 1].x = s[snakeLen - 2].x + 3;
					s[snakeLen - 1].y = s[snakeLen - 2].y;

					NewFruit(s, snakeLen, &fruitX, &fruitY);
					SSD1306_UpdateScreen();
				}
				if (checkColli(s, snakeLen, 3, 0) == 1) {
					end( snakeLen);
					break;

				}
				if ( s[0].x == 121 ) {
					uint8_t lastX = s[snakeLen - 1].x;
					uint8_t lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
					updateSnake(s, snakeLen);
					s[0].x = 1;
					s[0].y = s[0].y;

					lastX = s[snakeLen - 1].x;
					lastY = s[snakeLen - 1].y;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);
				}
				else {
					uint8_t lastX = s[snakeLen - 1].x;
					uint8_t lastY = s[snakeLen - 1].y;
					updateSnake(s, snakeLen);
					s[0].x += 3;

					SSD1306_DrawRectangle(s[0].x, s[0].y, 2, 2, 1);
					SSD1306_DrawRectangle(lastX, lastY, 2, 2, 0);

					SSD1306_UpdateScreen();
					count++;
					HAL_Delay(delay);
				}
				// check up and down
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 1) {
					l = 0;
					d = 0;
					r = 0;
					u = 1;

					break;
				}
				else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 1) {
					l = 0;
					u = 0;
					r = 0;
					d = 1;

					break;
				}
			}
		}
	}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
