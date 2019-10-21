#ifndef LOADER_H
#define LOADER_H

#include <QMutex>
#include <QObject>
#include <QPair>
#include <QTimer>
#include <QVector>
#include <QWaitCondition>

class Document;

class Loader : public QObject
{
	Q_OBJECT

	struct Stage
	{
		int file;
		int recordsLoaded;
		bool recordsLeft;

		Stage();
	};

	QMutex mutex;
	QWaitCondition toDo;
	QVector<QPair<Document*, Stage>> documents;

	std::unique_ptr<QTimer> timer;
	bool shouldStop;

public:
	Loader();

	QWaitCondition& hasThingsToDo();
	void stop();

private slots:
	void load();

public slots:
	void loadDocument(Document* document);
	void abortLoading(Document* document);

signals:
	void documentLoaded(Document* document);
	void documentNotLoaded(Document* document, const QString& error);
	void nextRecordGroup(Document* document, int records);
	void loadMessage(Document* document, const QString& message);
};

#endif // LOADER_H