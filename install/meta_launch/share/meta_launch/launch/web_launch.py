import os
from glob import glob
from setuptools import setup
from launch_ros.substitutions import FindPackageShare
import socket

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution, TextSubstitution
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from ament_index_python import get_package_share_directory

def get_own_ip():
    try:
        # Create a socket object
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Connect to a remote server (doesn't actually send any data)
        s.connect(("8.8.8.8", 80))
        # Get the local IP address
        ip_address = s.getsockname()[0]
        # Close the socket
        s.close()
        return ip_address
    except Exception as e:
        print("Error:", e)
        return None
    
package_name = 'meta_launch'

def generate_launch_description():

    launch_include = [
        IncludeLaunchDescription(
            XMLLaunchDescriptionSource([
                PathJoinSubstitution([
                    FindPackageShare('rosbridge_server'),
                    'launch',
                    'rosbridge_websocket_launch.xml'
                ])
            ]),
                launch_arguments={
                    'port': '9090',
                    'address': get_own_ip()
                }.items()
        ),
    ]

    print("Websocket server address: ", get_own_ip())


    return LaunchDescription(launch_include)
