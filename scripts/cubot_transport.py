#!/usr/bin/env python

'''
@Author: lifuguan
@Date: 2019-11-21 19:57:45
@LastEditTime: 2019-11-27 23:53:13
@LastEditors: Please set LastEditors
@Description: In User Settings Edit
@FilePath: /cubot/scripts/cubot_transport.py
'''

import rospy
from std_msgs.msg import String
import kociemba
import requests

solve_url = 'http://192.168.43.185/cube_group/code.txt'
delete_url = 'http://192.168.43.185/cube_group/delete.php'



dict = { 'U': 'a', "U\'": 'b', 'U2':'c', 'R':'d', 'R\'':'e', 'R2':'f', 'F':'g', 'F\'':'h', 'F2':'i', 'D':'j', 'D\'':'k', 'D2':'l','L':'m', 'L\'':'n', 'L2':'o', 'B':'p', 'B\'':'q', 'B2':'r'}

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('cubot', anonymous=True)
    rate = rospy.Rate(10)  
    msg_str = ""
    i = 0
    while(True):
        i += 1
        if i == 20:          
            i == 0
            r = requests.get(solve_url)
            # detected the file 
            if r.status_code == 200:
                msg_str = str(r.content)
                # trigger to delete
                requests.get(delete_url)
                break
            else:
                print "trying to read the file ... "
    print msg_str
    res_str = kociemba.solve(msg_str)
    list_ = res_str.split(" ")
    after_proc_str = ""
    for a in list_:
        after_proc_str += dict[a]
        #after_proc_str += ' '
    print after_proc_str     
    # broadcast in ROS
    while not rospy.is_shutdown():
        
        rospy.loginfo(after_proc_str)
        pub.publish(after_proc_str)
        rate.sleep()
    


if __name__ == '__main__':
    # r = requests.get(solve_url)
    # msg_str = str(r.content, encoding="utf-8")
    # print(msg_str)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
