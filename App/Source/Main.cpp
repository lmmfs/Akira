#include "Akira/Application.h"

#include "AppLayer.h"
//#include "OverLayer.h"

int main()
{
	Akira::ApplicationSpecification appSpec;
	appSpec.Name = "Architecture";
	appSpec.WindowSpec.Width = 1920;
	appSpec.WindowSpec.Height = 1080;

	Akira::Application application(appSpec);
	application.PushLayer<AppLayer>();
	//application.PushLayer<OverlayLayer>();

	application.Run();
}
