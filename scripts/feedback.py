#!/usr/bin/env python

import rospy
from rosplan_dispatch_msgs.msg import ActionFeedback

class Feedback():

	def __init__(self):

		self.feedback_pub = rospy.Publisher('rosplan_plan_dispatcher/action_feedback', ActionFeedback, queue_size = 1)

	def PubFeedback(self, action_id, status):

		feedback_msgs = ActionFeedback()
		feedback_msgs.action_id = action_id;
		feedback_msgs.status = status
		self.feedback_pub.publish(feedback_msgs)


if __name__ == '__main__':

	rospy.init_node('feedback_node')
	feedback = Feedback()
	action_id = 0
	status = "action achieved"
	rospy.sleep(0.1)
	feedback.PubFeedback(action_id, status)