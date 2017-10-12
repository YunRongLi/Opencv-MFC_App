#include <opencv2\opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <dshow.h>

#pragma comment(lib, "strmiids")

using namespace std;
using namespace cv;

//HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum) {
//	ICreateDevEnum *pDevEnum;
//	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
//
//	if (SUCCEEDED(hr)) {
//		hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
//
//		if (hr == S_FALSE) {
//			hr = VFW_E_NOT_FOUND;
//		}
//		pDevEnum->Release();
//	}
//	return hr;
//}
//
//void DisplayDeviceInformation(IEnumMoniker *pEnum){
//	IMoniker *pMoniker = NULL;
//	
//	while (pEnum->Next(1, &pMoniker, NULL) == S_OK){
//		IPropertyBag *pPropBag;
//		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
//
//		if (FAILED(hr))
//		{
//			pMoniker->Release();
//			continue;
//		}
//
//		VARIANT var;
//		VariantInit(&var);
//
//		// Get description or friendly name.
//		hr = pPropBag->Read(L"Description", &var, 0);
//
//		if (FAILED(hr)){
//			hr = pPropBag->Read(L"FriendlyName", &var, 0);
//
//		}
//		if (SUCCEEDED(hr)){
//			printf("Device Name: %S\n", var.bstrVal);
//			VariantClear(&var);
//
//		}
//
//		hr = pPropBag->Write(L"FriendlyName", &var);
//
//		// WaveInID applies only to audio capture devices.
//		hr = pPropBag->Read(L"WaveInID", &var, 0);
//		if (SUCCEEDED(hr)){
//			printf("WaveIn ID: %d\n", var.lVal);
//			VariantClear(&var);
//		}
//
//		hr = pPropBag->Read(L"DevicePath", &var, 0);
//		if (SUCCEEDED(hr)){
//			// The device path is not intended for display.
//			printf("Device path: %S\n", var.bstrVal);
//			VariantClear(&var);
//		}
//
//		pPropBag->Release();
//		pMoniker->Release();
//	}
//}

int main(int, char **) {

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}


	Mat video_mat;
	namedWindow("Show_Mat", 1);
	for (;;) {
		cap >> video_mat;
		imshow("Show_Mat", video_mat);
		if (waitKey(30) >= 0) {
			break;
		}
	}
	cap.release();
	return 0;

	/*HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr))
	{
		IEnumMoniker *pEnum;

		hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
		if (SUCCEEDED(hr))
		{
			DisplayDeviceInformation(pEnum);
			pEnum->Release();
		}*/
		/*hr = EnumerateDevices(CLSID_AudioInputDeviceCategory, &pEnum);
		if (SUCCEEDED(hr))
		{
			DisplayDeviceInformation(pEnum);
			pEnum->Release();
		}
		hr = EnumerateDevices(CLSID_AudioInputDeviceCategory, &pEnum);
		if (SUCCEEDED(hr))
		{
			DisplayDeviceInformation(pEnum);
			pEnum->Release();
		}*/
		//	CoUninitialize();
		//}
}
