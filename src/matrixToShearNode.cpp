/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
extractMatrixPosition node
This node returns the shear component of the input matrix as a vector.

    matrix (m) matrix

    output (o) double3
        outputXY (oxy) double
        outputXZ (oxz) double
        outputYZ (oyz) double

*/

#include "matrixToShearNode.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnData.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MTypeId.h>

// Input Attributes
MObject MatrixToShear::matrixAttr;

// Output Attributes
MObject MatrixToShear::outputAttr;
    MObject MatrixToShear::outputXYAttr;
    MObject MatrixToShear::outputXZAttr;
    MObject MatrixToShear::outputYZAttr;


void* MatrixToShear::creator()
{
    return new MatrixToShear();
}


MStatus MatrixToShear::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnMatrixAttribute m;
    MFnNumericAttribute n;

    matrixAttr = m.create("matrix", "m", MFnMatrixAttribute::Type::kDouble, &status);

    outputXYAttr = n.create("outputXY", "oxy", MFnNumericData::kDouble, 0.0, &status);
    outputXZAttr = n.create("outputXZ", "oxz", MFnNumericData::kDouble, 0.0, &status);
    outputYZAttr = n.create("outputYZ", "oyz", MFnNumericData::kDouble, 0.0, &status);

    outputAttr = c.create("output", "o", &status);
    c.addChild(outputXYAttr);
    c.addChild(outputXZAttr);
    c.addChild(outputYZAttr);
    c.setWritable(false);
    c.setStorable(false);

    addAttribute(matrixAttr);
    addAttribute(outputAttr);

    attributeAffects(matrixAttr, outputAttr);

    return MStatus::kSuccess;
}

MStatus MatrixToShear::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    if (plug == this->outputAttr || plug.parent() == this->outputAttr)
    {
        MMatrix mat = data.inputValue(matrixAttr).asMatrix();
        MTransformationMatrix t(mat);

        t.getShear(shear, MSpace::kWorld);
        
        MDataHandle outXY = data.outputValue(outputXYAttr);
        MDataHandle outXZ = data.outputValue(outputXZAttr);
        MDataHandle outYZ = data.outputValue(outputYZAttr);

        outXY.setDouble(shear[0]);
        outXZ.setDouble(shear[1]);
        outYZ.setDouble(shear[2]);

        outXY.setClean();
        outXZ.setClean();
        outYZ.setClean();

        data.setClean(outputAttr);
    } else {
        return MStatus::kUnknownParameter;
    }

    return MStatus::kSuccess;   
}