import rclpy
from rclpy.node import Node
import py_trees
import xml.etree.ElementTree as ET
import os
from geometry_msgs.msg import Pose2D
from std_msgs.msg import String

class WorldState(Node):
    def __init__(self):
        # Publishers
        super().__init__('world_state')
        self.pose_publisher = self.create_publisher(Pose2D, '/pose/command', 10)
        # self.task_publisher = rospy.Publisher("/strategy/state/current_task", StampedListString, queue_size=10)
        # Variables
        # self.team = rospy.get_param("team")
        self.node_parameters = {}
        self.pose = None
        self.task_done = False
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)
        # self.isArrivedAtTarget = False

    def timer_callback(self):
        # print("Timer Callback")
        pass    
    # def go_to_callback(self, data):
        # self.isArrivedAtTarget = data.data
        # print("Received Arrived at Target:", self.isArrivedAtTarget) # debug

    def task_done_callback(self, data):
        self.task_done = data.data
        print("[Strategy] Received Task Done:", self.task_done) # debug

    def pose_callback(self, data):
        self.pose = data.data
        print("Received Pose:", data.data)


class GoToTarget(py_trees.behaviour.Behaviour):
    def __init__(self, name, node_name, world_state):
        super(GoToTarget, self).__init__(name)
        self.node_name = node_name
        # self.has_reached_target = False
        self.has_done_task = False
        self.world_state = world_state

    def update(self):
        if self.has_done_task:
            return py_trees.common.Status.SUCCESS
        elif self.world_state.task_done:
            self.world_state.task_done = False
            self.has_done_task = True
            return py_trees.common.Status.SUCCESS
        else:
            # Publish to "/strategy/trajectory/command/pose"
            pose_msg = Pose2D()
            node_name = self.node_name
            pose_msg.data.pos.x = float(self.world_state.node_parameters[node_name]['x'])
            pose_msg.data.pos.y = float(self.world_state.node_parameters[node_name]['y'])
            pose_msg.data.ort.val = float(self.world_state.node_parameters[node_name]['ort_deg'])
            # Pakai x, y, ort dari worldstate kalau tidak ada di parameter
            if pose_msg.data.pos.x == None:
                pose_msg.data.pos.x = self.world_state.pose.pos.x
                pose_msg.data.pos.y = self.world_state.pose.pos.y
                pose_msg.data.ort.val = self.world_state.pose.ort.val
            self.world_state.pose_publisher.publish(pose_msg)
            self.world_state.pose = None
            # # Publish to "/strategy/state/current_task"
            # task_msg = StampedListString()
            # task_msg.data.data = ["GoToTarget", node_name]
            # world_state.task_publisher.publish(task_msg)
            return py_trees.common.Status.RUNNING    

class DoTask(py_trees.behaviour.Behaviour):
    def __init__(self, name, node_name, world_state):
        super(DoTask, self).__init__(name)
        self.node_name = node_name
        self.has_done_task = False
        self.world_state = world_state
    
    def update(self):
        if self.has_done_task:
            return py_trees.common.Status.SUCCESS
        elif self.world_state.task_done:
            self.world_state.task_done = False
            self.has_done_task = True
            return py_trees.common.Status.SUCCESS
        else:
            # Publish to "/strategy/state/current_task"
            # task_msg = StampedListString()
            # task_msg.data.data = ["DoTask", self.node_name]
            # world_state.task_publisher.publish(task_msg)
            return py_trees.common.Status.SUCCESS

def parse_tree_xml(xml_file, world_state):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    sequence = py_trees.composites.Sequence("MainSequence", memory=False)

    for child in root.find("Root").find("Sequence"):
        node_name = child.get("name")
        if child.tag == "GoToTarget":
            go_to_target = GoToTarget(name=node_name, node_name=node_name, world_state=world_state)
            # get parameters
            world_state.node_parameters[node_name] = {
                'x': child.get('x'),
                'y': child.get('y'),
                'ort_deg': child.get('ort_deg')
            }

            sequence.add_child(go_to_target)
        elif child.tag == "DoTask":
            do_task = DoTask(name=node_name, node_name=node_name, world_state=world_state)
            sequence.add_child(do_task)

    return sequence


def main(args=None):
    rclpy.init(args=args)

    world_state = WorldState()
    rclpy.spin(world_state)


    script_dir = os.path.dirname(os.path.abspath(__file__))
    file_xml="task.xml"
    xml_file_path = os.path.join(script_dir, file_xml)

    root = parse_tree_xml(xml_file_path, world_state)
    tree = py_trees.trees.BehaviourTree(root)
    tree.setup(timeout=15)
    py_trees.display.render_dot_tree(root, name="test_control_bt")


    rate = world_state.create_rate(1)
    while rclpy.ok():
        tree.tick()
        rate.sleep()

    # Render and save the tree structure to a dot file
    print('Hi from task.')


if __name__ == '__main__':
    main()
