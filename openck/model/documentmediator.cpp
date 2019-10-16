#include "documentmediator.hpp"

#include "../view/messageboxhelper.hpp"

DocumentMediator::DocumentMediator()
{
}

DocumentMediator::~DocumentMediator()
{
}

void DocumentMediator::clearFiles()
{
	documents.clear();
}

void DocumentMediator::newFile(const QStringList& files)
{
    documents.push_back(std::make_shared<Document>(files, true));
	loadRelatedFiles(files);
}

void DocumentMediator::openFile(const QStringList& files, bool isNew, QString author, QString desc)
{
    documents.push_back(std::make_shared<Document>(files, isNew));
	loadRelatedFiles(files);
}

void DocumentMediator::loadRelatedFiles(const QStringList& files)
{
	for (const auto& file : files)
	{
		documents.push_back(std::make_shared<Document>(QStringList(file), false));

		QStringList parents = documents.back()->getParentFiles();
		auto it = std::find_if(
			parents.begin(), parents.end(),
			[this](const QString& filename)
			{
				for (const auto& document : documents)
				{
					if (document->getSavePath() == filename)
					{
						return true;
					}
				}
				return false;
			}
		);

		if (it != parents.end())
		{
			documents.push_back(std::make_shared<Document>(QStringList(file), false));
		}
	}
}

void DocumentMediator::saveFile(const QString& path)
{
    if (documents.empty())
    {
        msgBoxCritical("No file open, cannot save.");
    }
    else
    {
        documents.back().get()->save(path);
    }
}

void DocumentMediator::setPaths(const FilePaths& filePaths)
{
    paths = filePaths;
}
