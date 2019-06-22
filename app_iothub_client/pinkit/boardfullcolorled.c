// https://github.com/ms-iotkithol-jp/IoTKitHoLV3/blob/master/PinKitIoTHubApp/PinKitIoTHubApp/PinKit/BoardFullColorLED.cs

#include <kernel.h>
#include "boardfullcolorled.h"
#include "pwmout_api.h"

// �e LED ���ڑ������|�[�g
pwmout_t portRed;     // ��
pwmout_t portGreen;   // ��
pwmout_t portBlue;    // ��

// �R���X�g���N�^�[
void BoardFullColorLED_Init()
{
	// �e LED �� InputPort �C���X�^���X
	pwmout_init(&portRed, LED_RED);
	pwmout_period_ms(&portRed, 2); // 500Hz

	pwmout_init(&portGreen, LED_GREEN);
	pwmout_period_ms(&portGreen, 2); // 500Hz

	pwmout_init(&portBlue, LED_BLUE);
	pwmout_period_ms(&portBlue, 2); // 500Hz
}

/// <summary>
/// �w��̐F�� LED ��_���A��������
/// </summary>
/// <param name="redOn">true �Ȃ�ΐԂ�_��</param>
/// <param name="greenOn">true �Ȃ�Η΂�_��</param>
/// <param name="blueOn">true �Ȃ�ΐ�_��</param>
void BoardFullColorLED_SetRgb(float redOn, float greenOn, float blueOn)
{
	pwmout_write(&portRed, redOn);
	pwmout_write(&portGreen, greenOn);
	pwmout_write(&portBlue, blueOn);
}

/// <summary>
/// �F���w��� LED ��_������
/// </summary>
/// <param name="color"></param>
void BoardFullColorLED_SetColor(Colors color)
{
	int redFlag = (int)color & (int)Colors_Red;
	int greenFlag = (int)color & (int)Colors_Green;
	int blueFlag = (int)color & (int)Colors_Blue;
	pwmout_write(&portRed, (redFlag != 0) ? 1.0 : 0.0);
	pwmout_write(&portGreen, (greenFlag != 0) ? 1.0 : 0.0);
	pwmout_write(&portBlue, (blueFlag != 0) ? 1.0 : 0.0);
}
