
(define (problem qualification_task)
(:domain hsr_domain)
(:objects
	blinky - robot
	kitchen dining_room bed table sink frigde - waypoint	
	grip - gripper
	c - cup
)
(:init
	(robot_at blinky dining_room)
	(undocked blinky)
	(allowed_goto_waypoint blinky)
	(empty grip)
	(dock_at dining_room)
	
)

(:goal (and
	
	(robot_at blinky kitchen)
	(holding grip c)	
	
)))
