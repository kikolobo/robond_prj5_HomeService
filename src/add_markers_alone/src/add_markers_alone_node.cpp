#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

void add_marker()
{

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_alone");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  enum State { PICKUP, HIDE, DROP, } state = PICKUP;
  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    marker.ns = "basic_shapes";
    marker.id = 0;

    marker.type = shape;

    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    //double pickUpPos[2]  = {-5.812, -4.261};
    //double dropOffPos[2] = {4.59, -4.76};
    if (state == State::PICKUP) {
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = -5.812;
      marker.pose.position.y = -4.261;
      marker_pub.publish(marker);
      ROS_INFO("Picking up ... ");
      sleep(5);
      state = State::HIDE;
    } else if (state == State::HIDE) {
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ROS_INFO("Hiding ...");
      sleep(5);
      state = State::DROP;
    } else {
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = 4.59;
      marker.pose.position.y = -4.76;
      marker_pub.publish(marker);
      ROS_INFO("Droping out ...");
      sleep(5);
    }

  }

}
