uint8_t msg_buffer[50] = {0};
uint16_t yaw_data, yaw_lsb, yaw_msb;
float yaw;

void BNO080_DMA_init(){
	for(int i=0; i<50; i++){
		if(msg_buffer[i]==0xAA && msg_buffer[i+1]==0xAA){
			yaw_lsb		= msg_buffer[i+3];
			yaw_msb		= msg_buffer[i+4];
			yaw_data	= yaw_msb<<8 | yaw_lsb;
			if(yaw_data>=0xB9B0){
				yaw = 360 + ((yaw_data - 0xFFFF) / 100.00);
			}
			else{
				yaw = yaw_data / 100.00;
			}
			break;
		}
	}
	HAL_UART_Receive_DMA(&huart1, msg_buffer, 50);
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
	BNO080_DMA_init();
}
