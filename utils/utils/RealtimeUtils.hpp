#ifndef REALTIME_UTILS_HPP
#define REALTIME_UTILS_HPP

/*
 * Utilities for realtime control
 *
 * Author: Andrew Barry, <abarry@csail.mit.edu> 2015
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include <bot_core/rotations.h>
#include <bot_frames/bot_frames.h>

#include "../../LCM/mav_pose_t.h"

#include <Eigen/Core>

#include "gtest/gtest.h"

/**
 * Converts mav_pose_t message into the Drake global frame.
 *
 * Supports an optional rotation matrix to rotate about yaw, allowing the user to use a local frame that sets
 * yaw to a specified value.
 */
Eigen::VectorXd StateEstimatorToDrakeVector(const mav_pose_t *msg, const Eigen::Matrix3d Mz = Eigen::Matrix3d::Identity());


Eigen::Matrix3d rpy2rotmat(Eigen::Vector3d rpy);
Eigen::Vector3d angularvel2rpydot(Eigen::Vector3d rpy, Eigen::Vector3d omega);
Eigen::Matrix3d angularvel2rpydotMatrix(Eigen::Vector3d rpy);
Eigen::Matrix3d quat2rotmat(Eigen::Vector4d q);
Eigen::Matrix3d rotz(double rotation_around_z);
Eigen::Vector3d rotmat2rpy(Eigen::Matrix3d rot_mat);

double deg2rad(double input_in_deg);

int64_t GetTimestampNow();

bool NonBlockingLcm(lcm_t *lcm);


#endif
