#ifndef FCM_H
#define FCM_H

#define MAX_DATA_POINTS 10000
#define MAX_CLUSTER 100
#define MAX_DATA_DIMENSION 5000

class FCM
{
public:
    FCM(double fuzziness, double epsilon);
    void init(double **data, int clusters, int num_points, int num_dimensions);
    void eval();
    double **getCenters();
    double **getMembershipMatrix();
    void printPoints();
    void saveClusters(const char *prefix);
    void saveMembershipMatrixU(const char *name);
    void saveCenters(const char *name);
    double getCenterAVG();


private:
    int num_data_points;
    int num_clusters;
    int num_dimensions;
    double low_high[MAX_DATA_DIMENSION][2];
    double degree_of_memb[MAX_DATA_POINTS][MAX_CLUSTER];
    double epsilon;
    double fuzziness;
    double data_point[MAX_DATA_POINTS][MAX_DATA_DIMENSION];
    double cluster_centre[MAX_CLUSTER][MAX_DATA_DIMENSION];


    void calculate_centre_vectors();
    double update_degree_of_membership();
    double get_new_value(int i, int j);
    double get_norm(int i, int j);
};

#endif // FCM_H
