#ifndef TRAJECTORY_TRAJLIB_HPP
#define TRAJECTORY_TRAJLIB_HPP

/*
 * Trajectory class representing a trajectory in state space
 *
 * Author: Andrew Barry, <abarry@csail.mit.edu> 2013-2015
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#include <bot_core/rotations.h>
#include <bot_frames/bot_frames.h>
#include <GL/gl.h>
#include <bot_lcmgl_client/lcmgl.h>

#include "../../externals/csvparser/csvparser.h"

#include <Eigen/Core>

using namespace std;

class Trajectory
{

    public:
        Trajectory();
        Trajectory(string filename_prefix, bool quiet = false); // loads a trajectory from a .csv file

        void LoadTrajectory(string filename_prefix, bool quiet = false);

        Eigen::MatrixXd GetGainMatrix(double t);

        int GetDimension() { return dimension_; }
        int GetUDimension() { return udimension_; }
        int GetTrajectoryNumber() { return trajectory_number_; }

        void Print();

        void GetTransformedPoint(int index, const BotTrans *transform, double *xyz);
        void PlotTransformedTrajectory(bot_lcmgl_t *lcmgl, const BotTrans *transform);

        double GetMaxTime();

        bool IsTimeInvariant() { return GetMaxTime() == 0; }

        Eigen::VectorXd GetState(double t);
        Eigen::VectorXd GetUCommand(double t);

        // returns the distance to the closest point on the trajectory
        // could optimize this with cover trees?
        //double DistanceToPoint(double x, double y, double z);




    private:

        Eigen::MatrixXd xpoints_;
        Eigen::MatrixXd upoints_;

        Eigen::MatrixXd kpoints_;
        Eigen::MatrixXd affine_points_;

        double dt_;


        int dimension_; // state space dimension
        int udimension_; // control input dimension

        int trajectory_number_;
        string filename_prefix_;

        void LoadMatrixFromCSV(const std::string& filename, Eigen::MatrixXd &matrix);

        int GetNumberOfLines(string filename);

        int GetIndexFromTime(double t);

};

#endif
