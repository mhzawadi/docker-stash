# Virtual endpoint forwarding requests to Authelia server.
location /auth_verify {
    internal;
    proxy_set_header            X-Real-IP $remote_addr;

    # Provide either X-Original-URL and X-Forwarded-Proto or
    # X-Forwarded-Proto, X-Forwarded-Host and X-Forwarded-URI or both.
    # Those headers will be used by Authelia to deduce the target url of the user.
    #
    # X-Forwarded-Proto is mandatory since Authelia uses the "trust proxy" option.
    # See https://expressjs.com/en/guide/behind-proxies.html
    proxy_set_header            X-Original-URL $scheme://$http_host$request_uri;

    proxy_set_header            X-Forwarded-Proto $scheme;
    proxy_set_header            X-Forwarded-Host $http_host;
    proxy_set_header            X-Forwarded-URI $request_uri;

    proxy_set_header            X-Forwarded-For $proxy_add_x_forwarded_for;

    # Authelia can receive Proxy-Authorization to authenticate however most of the clients
    # support Authorization instead. Therefore we rewrite Authorization into Proxy-Authorization.
    proxy_set_header            Proxy-Authorization $http_authorization;

    proxy_pass_request_body     off;
    proxy_set_header            Content-Length "";

    proxy_pass                  https://auth.mydomain.com/api/verify;
}
