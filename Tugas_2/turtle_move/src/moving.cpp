#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <cstdlib>

using namespace std;
using namespace ros;

void moveTurtle(Publisher &pub, double linear_x, double angular_z, int duration) {
    geometry_msgs::Twist move_cmd;
    move_cmd.linear.x = linear_x;  
    move_cmd.angular.z = angular_z; 
    Rate rate(1); // Frekuensi

    for (int i = 0; i < duration; ++i) {
        pub.publish(move_cmd);
        rate.sleep();
    }
}

void drawA(Publisher &pub, ServiceClient &teleport_client, turtlesim::TeleportAbsolute &teleport_srv) {
    // Memindahkan Turtle ke posisi (1,5)
    teleport_srv.request.x = 2.0; // X position
    teleport_srv.request.y = 5.0; // Y position
    teleport_srv.request.theta = 45.0; // Sudut
    teleport_client.call(teleport_srv); // Call Functionnya

    // Draw the letter
    moveTurtle(pub, 1.0, 0, 2); // Move diagonally upward

    moveTurtle(pub, 0, -1.0, 2); // Rotate ke kiri bawah
    moveTurtle(pub, 1.0, 0, 2); // Move diagonally downward

    moveTurtle(pub,0, 1.57, 2);
    moveTurtle(pub, 0.6, 0, 2);
    moveTurtle(pub, 0, 0.48, 2);
    moveTurtle(pub,0.43, 0, 2);

    moveTurtle(pub, 0, -1.57, 2);
    moveTurtle(pub, 0.43, 0, 2);

    moveTurtle(pub, 0, -0.48, 2);
    moveTurtle(pub, 0.6, 0, 2);
}

void drawD(Publisher &pub, ServiceClient &teleport_client, turtlesim::TeleportAbsolute &teleport_srv) {
    teleport_srv.request.x = (teleport_srv.request.x + 2.5); // Pindah 2.5 unit ke kanan dari posisi akhir huruf "A"
    teleport_srv.request.y = teleport_srv.request.y; // Pertahankan posisi Y
    teleport_srv.request.theta = 0.0; // Reset sudut
    teleport_client.call(teleport_srv);

    // Draw the letter
    moveTurtle(pub, 0, 0.785, 2); // Mengubah sudut ke arah atas
    moveTurtle(pub, 1.0, 0, 2); // Move straight upward
    moveTurtle(pub, 0, -0.785, 2); // Mengeubah sudut ke arah kanan
    moveTurtle(pub, 0.8, -0.785, 4); // Setengah Lingkaran
}

void drawI(Publisher &pub, ServiceClient &teleport_client, turtlesim::TeleportAbsolute &teleport_srv) { 
    teleport_srv.request.x = (teleport_srv.request.x + 1.6); // Pindah 1.6 unit ke kanan dari posisi akhir huruf "D"
    teleport_srv.request.y = teleport_srv.request.y; // Pertahankan posisi Y
    teleport_srv.request.theta = 0.0; // Orientation (angle)
    teleport_client.call(teleport_srv);

    // Draw the letter
    moveTurtle(pub, 0, 0.785, 2); // Menggok mas pokoke
    moveTurtle(pub, 1.0, 0.0, 2); // Maju maju maju
}

void drawT(Publisher &pub, ServiceClient &teleport_client, turtlesim::TeleportAbsolute &teleport_srv) {
    teleport_srv.request.x = (teleport_srv.request.x); // Pertahankan posisi X
    teleport_srv.request.y = (teleport_srv.request.y); // Turun
    teleport_client.call(teleport_srv);

    teleport_srv.request.x = (teleport_srv.request.x+1.6); // Pindah 1.6 unit ke kanan dari posisi akhir huruf "I"
    teleport_srv.request.y = (teleport_srv.request.y); // Pertahankan posisi Y
    teleport_client.call(teleport_srv);

    // Draw vertical line
    moveTurtle(pub, 0  , 0.785, 2);
    moveTurtle(pub, 1.0, 0.0  , 2); // Move straight downward

    moveTurtle(pub,0, 0.785, 2);
    moveTurtle(pub,0.6, 0, 2);
    moveTurtle(pub,0, 1.57, 2);
    moveTurtle(pub,1.2, 0 , 2);
}

int main(int argc, char** argv) {
    init(argc, argv, "draw_adit");
    NodeHandle nh;

    // Create a publisher for turtle movement
    Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // Create a service client for teleporting the turtle
    ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    turtlesim::TeleportAbsolute teleport_srv;
    teleport_srv.request.x = 2.0; // X position
    teleport_srv.request.y = 5.0; // Y position (bottom left of "A")
    teleport_client.call(teleport_srv);

    // Reset Turtlesim
    system("rosservice call /clear");

    // Draw each letter
    drawA(pub, teleport_client, teleport_srv);
    drawD(pub, teleport_client, teleport_srv);
    drawI(pub, teleport_client, teleport_srv);
    drawT(pub, teleport_client, teleport_srv);

    return 0;
}