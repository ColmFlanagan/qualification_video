
(define (domain hsr_domain)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)

(:types
	robot
	waypoint
	cup
	gripper
)

(:predicates

	;;robot predicates

	(robot_at ?r - robot ?wp - waypoint)
	(undocked ?r - robot)
	(docked ?r - robot)
	(localised ?r - robot)
	(allowed_goto_waypoint ?r - robot)
	(empty ?grip - gripper)
	(holding ?grip - gripper ?c - cup)
	(dock_at ?wp - waypoint)
	(visited ?wp - waypoint)
	
)


(:action goto_waypoint
	:parameters (?r - robot ?from ?to - waypoint)
	
	:precondition (and
		(undocked ?r)
		(robot_at ?r ?from)
		(allowed_goto_waypoint ?r)
		)
	:effect (and
		(robot_at ?r ?to)
		(not (robot_at ?r ?from))
		(not (allowed_goto_waypoint ?r))
		)
)

(:action grasp
	:parameters(?r - robot ?g - gripper ?c - cup ?cup_loc - waypoint)
	
	:precondition (and
		(undocked ?r)
		(robot_at ?r ?cup_loc)
		(empty ?g)

	)
	:effect (holding ?g ?c)
)

;; Dock to charge
(:action dock
	:parameters (?r - robot ?wp - waypoint)
	
	:precondition 
		(and
		(dock_at ?wp)
		(robot_at ?r ?wp)
		(undocked ?r)
		)
	:effect (and
		(docked ?r)
		(not (undocked ?r))
		)
)

(:action undock
	:parameters (?r - robot ?wp - waypoint)
	
	:precondition 
		(and
		(dock_at ?wp)
		(docked ?r)
		)
	:effect (and
		(not (docked ?r))
		(undocked ?r)
		)
)


;; Localise
(:action localise
	:parameters (?r - robot)
	
	:precondition (undocked ?r)
	:effect (localised ?r)
)




)



