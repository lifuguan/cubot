#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import kociemba
import requests

solve_url = 'http://192.168.43.185/cube_group/code.txt'
delete_url = 'http://192.168.43.185/cube_group/delete.php'


def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('cubot', anonymous=True)
    rate = rospy.Rate(10)  
    msg_str = ""
    
    while(True):
        r = requests.get(solve_url)
        # detected the file 
        if r.status_code == 200:
            msg_str = str(r.content)
            # trigger to delete
            requests.get(delete_url)
            break
        else:
            print "trying to read the file ... "

    # broadcast in ROS
    while not rospy.is_shutdown():
        res_str = kociemba.solve(msg_str)
        rospy.loginfo(res_str)
        pub.publish(res_str)
        rate.sleep()
    


if __name__ == '__main__':
    # r = requests.get(solve_url)
    # msg_str = str(r.content, encoding="utf-8")
    # print(msg_str)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
