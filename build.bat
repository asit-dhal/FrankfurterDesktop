@echo on

pushd %~dp0

if exit JUCE goto :BUILD
git clone https://github.com/WeAreROLI/JUCE.git
pushd %~dp0
cd JUCE
git apply ..\juce_lgpl.ptch
popd

:BUILD
pushd %~dp0
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cd "JUCE\extras\Projucer\Builds\VisualStudio2017"
msbuild.exe Projucer.sln /t:Build /p:Configuration=Release;Platform=x64
popd

cd "CurrencyExchange\Builds\VisualStudio2017"
devenv.exe CurrencyExchange.sln
popd