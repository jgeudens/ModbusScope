
#include <QtTest/QtTest>

#include "updateregisteroperations.h"

#include "testupdateregisteroperations.h"


void TestUpdateRegisterOperations::init()
{

}

void TestUpdateRegisterOperations::cleanup()
{

}

void TestUpdateRegisterOperations::noOperation()
{
    ProjectFileData::RegisterSettings regSettings;

    checkOperation(regSettings, QStringLiteral("VAL"));
}

void TestUpdateRegisterOperations::bitmask()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.bitmask = 255;

    checkOperation(regSettings, QStringLiteral("VAL&0xFF"));
}

void TestUpdateRegisterOperations::shiftLeft()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.shift = 1;

    checkOperation(regSettings, QStringLiteral("VAL<<1"));
}

void TestUpdateRegisterOperations::shiftRight()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.shift = -1;

    checkOperation(regSettings, QStringLiteral("VAL>>1"));
}

void TestUpdateRegisterOperations::multiply()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.multiplyFactor = 2;

    checkOperation(regSettings, QStringLiteral("VAL*2"));
}

void TestUpdateRegisterOperations::divide()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.divideFactor = 2;

    checkOperation(regSettings, QStringLiteral("VAL/2"));
}

void TestUpdateRegisterOperations::allOperations()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.multiplyFactor = 3;
    regSettings.divideFactor = 2;
    regSettings.shift = 1;
    regSettings.bitmask = 255;

    checkOperation(regSettings, QStringLiteral("((VAL&0xFF)<<1)*3/2"));
}

void TestUpdateRegisterOperations::bitmaskShift()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.shift = 2;
    regSettings.bitmask = 21930;

    checkOperation(regSettings, QStringLiteral("(VAL&0x55AA)<<2"));
}

void TestUpdateRegisterOperations::bitmaskMultiply()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.multiplyFactor = 2;
    regSettings.bitmask = 4294967040;

    checkOperation(regSettings, QStringLiteral("(VAL&0xFFFFFF00)*2"));
}

void TestUpdateRegisterOperations::bitmaskSigned16()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.b32Bit = false;
    regSettings.bUnsigned = false;
    regSettings.bitmask = 0xFFFF;

    checkOperation(regSettings, QStringLiteral("VAL"));
}

void TestUpdateRegisterOperations::bitmaskSigned32()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.b32Bit = true;
    regSettings.bUnsigned = false;
    regSettings.bitmask = 0xFFFFFFFF;

    checkOperation(regSettings, QStringLiteral("VAL"));
}

void TestUpdateRegisterOperations::shiftDivide()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.shift = 2;
    regSettings.divideFactor = 3;

    checkOperation(regSettings, QStringLiteral("(VAL<<2)/3"));
}

void TestUpdateRegisterOperations::multiplyDivide()
{
    ProjectFileData::RegisterSettings regSettings;

    regSettings.multiplyFactor = 2;
    regSettings.divideFactor = 3;

    checkOperation(regSettings, QStringLiteral("VAL*2/3"));
}

void TestUpdateRegisterOperations::checkOperation(ProjectFileData::RegisterSettings& regSettings, QString regResult)
{
    QString regOperation;

    UpdateRegisterOperations::convert(regSettings, regOperation);

    QCOMPARE(regOperation, regResult);
}


QTEST_GUILESS_MAIN(TestUpdateRegisterOperations)
