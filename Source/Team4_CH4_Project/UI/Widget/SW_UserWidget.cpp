// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_UserWidget.h"

void USW_UserWidget::SetWidgetController(USW_WidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet(); // �������Ʈ���� ������ �ʱ�ȭ ���� ����.
}
void USW_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
// ������ WidgetController �� ���� �Ǹ� �� ��Ʈ�ѷ��� ������� UI �� �ʱ�ȭ �ϰų� ���ε��� ����.
// UserWidget �� WidgetController �� ���õǴ� ������ ��ǻ��� �ʱ�ȭ Ÿ�̹��̴�.
// ���� �� ������ ���缭 WidgetControllerSet() �� ȣ���Ͽ� �������Ʈ���� ������ �ð����� ������ �����Ѵ�.
