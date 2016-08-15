#pragma once

class FernStyle {
public:
	ofPoint
		branchAngle,
		branchVariation,
		trunkAngle,
		trunkVariation,
		leftBranchAngle,
		rightBranchAngle,
		leftTrunkAngle,
		rightTrunkAngle,
		leafVariation;

	float
		branchScaling,
		trunkScaling,
		minLength,
		leafScale,
		branchWidth,
		leafGrowth,
		overallGrowth;

	float baseLength;
};
