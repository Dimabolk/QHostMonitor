#include "startup.h"
#include "qMainForm.h"
#include "monitoringService.h"
#include "actionService.h"
#include "logService.h"
#include "hmListService.h"
#include "global/tAction.h"
#include "global/ioActionProfileLoader.h"
#include "global/ioTestMethodLoader.h"
#include "global/ioUserVarsLoader.h"
#include "global/ioMailProfileLoader.h"
#include "global/ioColorProfileLoader.h"
#include "global/ioUserProfileLoader.h"
#include "tNode.h"
#include "tView.h"
#include "utils.h"

#include <QCoreApplication>
#include <QFile>
#include <QDir>

namespace SDPO {

/******************************************************************/

Startup::Startup() :
    QObject(NULL),
    m_mainForm(*new MainForm(NULL)),
    m_HML(*new HMListService(this)),
    m_testRunner(*new MonitoringService()),
    m_actionService(*new ActionService(&m_HML)),
    m_logService(*new LogService())
{
    connect(&m_mainForm, SIGNAL(testingPaused(bool)), &m_testRunner, SLOT(setPaused(bool)));

    TEnums::init();
    load();

    m_mainForm.setupFolders(&m_HML);
    m_mainForm.init();
    m_mainForm.resetScriptMenu();

    connect(m_HML.rootItem(), SIGNAL(readyRun(TNode*)), &m_testRunner, SLOT(runTest(TNode*)));
    connect(m_HML.rootItem(), SIGNAL(testUpdated(TNode*)), &m_actionService, SLOT(runActions(TNode*)));
    connect(m_HML.rootItem(), SIGNAL(testUpdated(TNode*)), &m_logService, SLOT(writeLog(TNode*)));
    connect(&m_logService, SIGNAL(logAlert(int,TTest*,bool)), &m_actionService, SLOT(runProfile(int,TTest*,bool)));
    connect(&m_actionService, SIGNAL(actionWinPopup(TTest*)), &m_mainForm, SLOT(onActionWinPopup(TTest*)), Qt::QueuedConnection);
    connect(&m_actionService, SIGNAL(actionWriteCommonLog(TTest*)), &m_logService, SLOT(writeCommonLog(TTest*)), Qt::QueuedConnection);
    connect(&m_actionService, SIGNAL(actionWritePrivateLog(TTest*)), &m_logService, SLOT(writePrivateLog(TTest*)), Qt::QueuedConnection);
    connect(&m_actionService, SIGNAL(actionWriteSpecificFileLog(TTest*,QString)), &m_logService, SLOT(writeSpecificFileLog(TTest*,QString)), Qt::QueuedConnection);
}

/******************************************************************/

Startup::~Startup()
{
    Utils::DestructorMsg(this);
    m_testRunner.clear();
    delete &m_mainForm;
    delete &m_testRunner;
    delete &m_actionService;
    delete &m_logService;
    delete &m_HML;
}

/******************************************************************/

void Startup::show() const
{
    m_mainForm.show();
}

/******************************************************************/

void Startup::load() {
    TAction::init();
    loadUserDefinedVariables();
    loadTestMethodDescription();
    loadActionProfiles();
    loadMailProfiles();
    loadColorProfiles();
    loadUserProfiles();
    GData::currentUser = "local";
    checkScriptsDir();
    loadFoldersModel();
}

/******************************************************************/

void Startup::loadUserDefinedVariables()
{
    IOUserVarsLoader loader;
    loader.load();
}

/******************************************************************/

void Startup::loadTestMethodDescription()
{
    IOTestMethodLoader loader;
    loader.load();
}

/******************************************************************/

void Startup::loadActionProfiles()
{
    IOActionProfileLoader loader;
    loader.load();
}

/******************************************************************/

void Startup::loadMailProfiles()
{
    IOMailProfileLoader loader;
    loader.load();
}

/******************************************************************/

void Startup::loadColorProfiles()
{
    IOColorProfileLoader loader;
    loader.load();
}

/******************************************************************/

void Startup::loadUserProfiles()
{
    IOUserProfileLoader loader;
    loader.load();
}

/******************************************************************/

void Startup::checkScriptsDir() {
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(path);
    if (!dir.cd("scripts")) {
        qDebug() << "scripts subdir does not exists";
        if (!dir.mkdir("scripts")) {
            qDebug() << "Cannot create scripts subdir";
        }
    }
}

/******************************************************************/

void Startup::loadFoldersModel() {
    TRoot *root = m_HML.rootItem();
    TNode* views = root->rootView();
    TFolder *folder = qobject_cast<TFolder*>(root->rootFolder());

    TView *vAllBadItems = new TView("all bad items",folder);
    root->addNode(views, vAllBadItems);
    vAllBadItems->setSelectByStatus(true);
    vAllBadItems->addStatusCriteria(TView::VS_BadNew);
    vAllBadItems->addStatusCriteria(TView::VS_BadAcknowleged);

    TView *vBadWarning = new TView("bad & warning",folder);
    root->addNode(views, vBadWarning);
    vBadWarning->setSelectByStatus(true);
    vBadWarning->addStatusCriteria(TView::VS_BadNew);
    vBadWarning->addStatusCriteria(TView::VS_BadAcknowleged);
    vBadWarning->addStatusCriteria(TView::VS_UnknownNew);
    vBadWarning->addStatusCriteria(TView::VS_UnknownAcknowleged);
    vBadWarning->addStatusCriteria(TView::VS_WarningNew);
    vBadWarning->addStatusCriteria(TView::VS_WarningAcknowleged);

    TView *vNonAcknowleged = new TView("non asknowleged",folder);
    root->addNode(views, vNonAcknowleged);
    vNonAcknowleged->setSelectByStatus(true);
    vNonAcknowleged->addStatusCriteria(TView::VS_BadNew);
    vNonAcknowleged->addStatusCriteria(TView::VS_UnknownNew);
    vNonAcknowleged->addStatusCriteria(TView::VS_WarningNew);

    TView *vDisabled = new TView("disabled",folder);
    root->addNode(views, vDisabled);
    vDisabled->setSelectByStatus(true);
    vDisabled->addStatusCriteria(TView::VS_Disabled);

    TView *vDeadTime5 = new TView("DeadTime > 5%",folder);
    root->addNode(views, vDeadTime5);
    vDeadTime5->setSelectByStats(true);
    vDeadTime5->setStatsCriteria(TView::VC_DeadRatio);
    vDeadTime5->setDeadRatioValue(5.0);

    TView *vDeadTime10 = new TView("DeadTime > 10%",folder);
    root->addNode(views, vDeadTime10);
    vDeadTime10->setSelectByStats(true);
    vDeadTime10->setStatsCriteria(TView::VC_DeadRatio);
    vDeadTime10->setDeadRatioValue(10.0);

    TView *vStatusChanged = new TView("Recent status changed",folder);
    root->addNode(views, vStatusChanged);
    vStatusChanged->setSelectByStats(true);
    vStatusChanged->setStatsCriteria(TView::VC_Duration);
    vStatusChanged->setDurationGreater(false);
    vStatusChanged->setDurationValue(20);
}

/******************************************************************/

} // namespace SDPO


