#include "test_suite.h"
#include <QDebug>
#include <QtTest/QtTest>

using namespace trdrop;

int main(int argc, char* argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    qDebug() << "Starting all test suite(s)";
    qDebug() << "-------------------------------";
    qDebug() << "> Accessing tests from " << &TestSuite::test_list();
    qDebug() << TestSuite::test_list().size() << "test suites(s) detected";

    int failedTestsCount = 0;
    for (TestSuite* i : TestSuite::test_list()) {
        qDebug() << "-------------------------------";
        qDebug() << "> Executing test" << i->test_name;
        QString filename(i->test_name + ".xml");
        int result = QTest::qExec(i, QStringList() << " "
                                                   << "-o" << filename << "-xunitxml");
        if (result == 0) {
            qDebug() << "Test result: Success!";
        } else {
            qDebug() << "Test result: Failure with" << result << "error(s)";
            failedTestsCount++;
        }
    }
    qDebug() << "-------------------------------";
    qDebug() << "All tests complete:"
             << failedTestsCount << "failure(s) detected.";
    qDebug() << "-------------------------------";
    return 0;
}
