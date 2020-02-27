# docker-stash
A stash of docker compose and stacks

This repo has 2 types of compse, the first is standalone docker-compse.
The second is a stack to run on docker swarm, all thr stacks have a line you can use to run them.

### Conventions

All the files have had custom config removed, all domains are `mydomain.com`.

please update any files you use with your own passwords and other settings.


### Using NFS

I have used NFS for some of my own services, below is an example you can use to setup.

```
volumes:
  authelia:
    driver: local
    driver_opts:
      type: 'nfs'
      o: "addr=192.168.1.1,rw,noatime,rsize=8192,wsize=8192,tcp,timeo=14"
      device: ':/location/on/the/nfs/server/authelia'
```
