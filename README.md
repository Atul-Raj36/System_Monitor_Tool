# System_Monitor_Tool

<p>A terminal-based system monitoring tool written in C++ that displays real-time CPU, memory, and process information, similar to the Linux top command.
It also allows sorting processes by CPU or memory and killing processes directly from the interface.</p>

<h3>Features</h3>
<ul>
  <li>Display CPU usage, memory usage, and system uptime in real-time.</li>
  <li> List all running processes with:</li>
     <ul>
         <li>PID</li>
         <li>Process Name</li>
         <li>CPU usage</li>
         <li>memory usage</li>
     </ul>
  <li>Sort processes dynamically by:</li>
      <ul>
        <li>CPU usage</li>
        <li>Memory usage</li>
      </ul>
  <li>Kill processes by entering the PID.</li>
  <li>Refreshes automatically every 1–2 seconds for real-time monitoring.</li>
</ul>
<h3>Project Structure</h3>
<ul>system_monitor/
  <li>main.cpp </li>
  <li>system_info.h   </li>
  <li> system_info.cpp</li>
  <li>process_info.h </li>
  <li> process_info.cpp</li>
</ul>
<h3>Compilation</h3>
<p>command : g++ main.cpp system_info.cpp process_info.cpp -o system_monitor -std=c++11 -pthread </p>
<h3>Running the program</h3>
<p>./system_monitor</p>
