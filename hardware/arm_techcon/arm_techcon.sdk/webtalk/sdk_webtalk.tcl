webtalk_init -webtalk_dir C:\\arm_techcon\\arm_techcon.sdk\\webtalk
webtalk_register_client -client project
webtalk_add_data -client project -key date_generated -value "Wed Oct 26 13:26:18 2016" -context "software_version_and_target_device"
webtalk_add_data -client project -key product_version -value "SDK v2016.1" -context "software_version_and_target_device"
webtalk_add_data -client project -key build_version -value "2016.1" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_platform -value "amd64" -context "software_version_and_target_device"
webtalk_add_data -client project -key registration_id -value "" -context "software_version_and_target_device"
webtalk_add_data -client project -key tool_flow -value "SDK" -context "software_version_and_target_device"
webtalk_add_data -client project -key beta -value "false" -context "software_version_and_target_device"
webtalk_add_data -client project -key route_design -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_family -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_device -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_package -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_speed -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key random_id -value "692hnotan9r09vhc6kqq48vcle" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_id -value "2016.1_24" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_iteration -value "24" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_name -value "" -context "user_environment"
webtalk_add_data -client project -key os_release -value "" -context "user_environment"
webtalk_add_data -client project -key cpu_name -value "" -context "user_environment"
webtalk_add_data -client project -key cpu_speed -value "" -context "user_environment"
webtalk_add_data -client project -key total_processors -value "" -context "user_environment"
webtalk_add_data -client project -key system_ram -value "" -context "user_environment"
webtalk_register_client -client sdk
webtalk_add_data -client sdk -key uid -value "1477508753354" -context "sdk\\\\bsp/1477508753354"
webtalk_add_data -client sdk -key hwid -value "1477168987562" -context "sdk\\\\bsp/1477508753354"
webtalk_add_data -client sdk -key os -value "standalone" -context "sdk\\\\bsp/1477508753354"
webtalk_add_data -client sdk -key apptemplate -value "zynq_fsbl" -context "sdk\\\\bsp/1477508753354"
webtalk_add_data -client sdk -key uid -value "1477508776781" -context "sdk\\\\application/1477508776781"
webtalk_add_data -client sdk -key hwid -value "1477168987562" -context "sdk\\\\application/1477508776781"
webtalk_add_data -client sdk -key bspid -value "1477508753354" -context "sdk\\\\application/1477508776781"
webtalk_add_data -client sdk -key newbsp -value "true" -context "sdk\\\\application/1477508776781"
webtalk_add_data -client sdk -key os -value "standalone" -context "sdk\\\\application/1477508776781"
webtalk_add_data -client sdk -key apptemplate -value "zynq_fsbl" -context "sdk\\\\application/1477508776781"
webtalk_transmit -clientid 1868713273 -regid "" -xml C:\\arm_techcon\\arm_techcon.sdk\\webtalk\\usage_statistics_ext_sdk.xml -html C:\\arm_techcon\\arm_techcon.sdk\\webtalk\\usage_statistics_ext_sdk.html -wdm C:\\arm_techcon\\arm_techcon.sdk\\webtalk\\sdk_webtalk.wdm -intro "<H3>SDK Usage Report</H3><BR>"
webtalk_terminate
