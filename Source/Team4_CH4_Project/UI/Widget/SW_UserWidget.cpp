// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_UserWidget.h"

void USW_UserWidget::SetWidgetController(USW_WidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet(); // 블루프린트에서 구현할 초기화 로직 실행.
}
void USW_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
// 위젯이 WidgetController 를 갖게 되면 그 컨트롤러를 기반으로 UI 를 초기화 하거나 바인딩을 설정.
// UserWidget 은 WidgetController 가 세팅되는 시점이 사실상의 초기화 타이밍이다.
// 따라서 그 시점에 맞춰서 WidgetControllerSet() 를 호출하여 블루프린트에서 구현한 시각적인 세팅을 시작한다.
