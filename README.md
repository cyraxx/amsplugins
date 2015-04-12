# Two access plugins for Adobe Media Server

### What's all this?
These are two access plugins for Adobe Media Server that prevent non-authorized clients from publishing to your server. They are currently for the 64-bit Linux edition of AMS only.

##### But doesn't Adobe already supply an authentication plugin for this very purpose?
Yes they do, but it has two major flaws:

1. It's very easily circumvented. It only checks those clients that connect with an FMLE user-agent string. Any client that supplies a different user-agent string (which, for example, Wirecast does by default) is simply let through without any authentication whatsoever.
2. It only supports clients that implement Adobe's challenge-response authentication protocol, which many standard RTMP clients don't.

##### How do your plugins fix this?
There are actually two separate plugins for two separate use cases:
* The **chain** plugin. It chain-loads Adobe's original access plugin and passes off any connection from FMLE to that plugin so that the usual user/password authentication system can be used. However, it also fixes the big security problem that Adobe's plugin has by revoking write access for all non-FMLE clients so they won't be able to publish. Use this plugin if you only use encoders supporting Adobe's FMLE authentication system (such as FMLE and Wirecast).

* The **key** plugin. It requires all clients with certain user-agents that are regarded as publishers (FMLE, Wirecast, others can be added if needed) to supply a valid key with the RTMP URL they're connecting to. This is a little less secure than the chain plugin because the key will be transmitted in plain text but gives you more flexibility because it works with any regular RTMP client.

##### Couldn't the same thing be done with server-side ActionScript or by using an auth plugin instead of an access plugin?
Yes, but not if you're running the (less expensive) AMS Standard Edition which doesn't support either of those. Basically, the only way to run custom code in AMS Standard is with access plugins like these.

##### Do these plugins also work with the `livepkgr` application?
Yes. In the examples below I've only listed RTMP URLs using the `live` application but these plugins will work for any AMS application.

### How to use the chain plugin

1. Install and configure Adobe's FMLE authentication add-in regularly. Check that password authentication works with FMLE.
2. Make sure g++ and make are installed.
3. Change into your AMS access plugin directory (usually `/opt/adobe/ams/modules/access`) and rename `libconnect.so` to `libconnect_chain.so`.
4. Change into the `chain` source directory and run `make`. It should compile without errors.
5. If your AMS is not installed in `/opt/adobe/ams`, adjust the InstallDir line in `Makefile`.
6. As superuser, run `make install`.
7. Restart AMS. You should see a line like `Auth adaptor chain loaded from ...` in syslog and no error messages after that.
8. You're done. Check that you can still publish with FMLE but can't with, for example, Wirecast.

**Note:** If you're using Wirecast with the chain plugin, you need to set its user-agent to FMLE in the streaming settings.

### How to use the key plugin

1. Create a file called `keys` in your AMS configuration directory (usually `/opt/adobe/ams/conf`) and enter some access keys of your choice, one per line.
2. Make sure g++ and make are installed.
3. Change into the `key` source directory and run `make`. It should compile without errors.
4. If your AMS is not installed in `/opt/adobe/ams`, adjust the InstallDir line in `Makefile`.
5. As superuser, run `make install`.
6. Restart AMS. You should see the line `Initializing key access adaptor` in syslog.
7. You're done. Check that you can still publish when supplying a valid key (see below) but can't when not supplying a key.

To publish, you now need to append `?key=` and one of the keys from your `keys` file to your RTMP URL (**not** the stream name!), for example: `rtmp://yourserver/live?key=...`

If your encoder takes the RTMP URL and the stream name as one combined string, it needs to look like this: `rtmp://yourserver/live?key=.../livestream`

**Note:** If you're not using FMLE or Wirecast as your encoder, make sure it uses one of the user-agent strings listed in the plugin's source code (add yours if necessary) so it will be regarded as a publisher by the plugin. If, for example, you're using ffmpeg to send an RTMP stream to your server, you need to tell it to use the proper user-agent string like so: `ffmpeg ... -rtmp_flashver FMLE/3.0 -f flv "rtmp://yourserver/live?key=.../livestream"`
