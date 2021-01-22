## Bugs
# gazebo.launch နဲ့ controller.launch တွဲပြီး launch လုပ်ရင် Gazebo မှာ robot ပုံစံမမှန်ပါ။ 
# <rosparam file="$(find rom1_simulation)/config/rom1_control.yaml" command="load"/> ကို ေစာလျင်စွာထည့်လို့ဖြစ်သည်။ yaml ထဲမှာ gazebo_ros_control pid ကြောင့် ပြသနာဖြစ်ပါသည်။ comment အုပ်ပါ။