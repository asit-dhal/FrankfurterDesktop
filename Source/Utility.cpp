/*
  ==============================================================================

    Utility.cpp
    Created: 18 Feb 2019 9:31:06pm
    Author:  asitd

  ==============================================================================
*/

#include "Utility.h"

GlobalInstance::GlobalInstance(): m_threadPool(3)
{
    loadIconsFromZipFile();
}

ThreadPool& GlobalInstance::getThreadPool()
{
	return m_threadPool;
}

Drawable* GlobalInstance::getIcon(String iconName)
{
    iconName += ".svg";
    auto indexOfItem = m_iconNames.indexOf(iconName);
    if (indexOfItem != -1)
        return m_iconsFromZipFile[indexOfItem]->createCopy();
    else
        return nullptr;
}

void GlobalInstance::loadIconsFromZipFile()
{
    auto assetsDir = File::getSpecialLocation(File::currentExecutableFile);
    auto resourceFile = assetsDir.getParentDirectory().getChildFile("icons.zip");
    jassert(resourceFile.existsAsFile());
    ZipFile icons(resourceFile);
    for (auto i = 0; i < icons.getNumEntries(); ++i)
    {
        std::unique_ptr<InputStream> svgFileStream(icons.createStreamForEntry(i));
        if (svgFileStream.get() != nullptr)
        {
            m_iconNames.add(icons.getEntry(i)->filename);
            m_iconsFromZipFile.add(Drawable::createFromImageDataStream(*svgFileStream));
        }
    }
}

JUCE_IMPLEMENT_SINGLETON(GlobalInstance);
